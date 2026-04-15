/**
 * @file    app_netxduo.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the base init of NetXDuo stack.
 * @version 0.1
 * @date    2026-03-05
 *
 * @copyright Copyright (c) 2026
 *
 */

// Just a quick logger config
#define LOG_MODULE "NETX_APP"

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "app_netxduo.h"

// Local libraries
#include "app_netxduo_status.h"
#include "logger.h"
#include "nx_stm32_eth_driver.h"

// ThreadX
#include "tx_api.h"
#include "tx_handler.h"

// NetXDuo
#include "nx_api.h"
#include "nx_udp.h"

// Addons
#include "nxd_dhcp_client.h"
#include "nxd_telnet_server.h"

// STD
#include <sys/cdefs.h>

// ======================================================================
//                               EXTERNS
// ======================================================================

extern void Error_Handler();

// ======================================================================
//                              VARIABLES
// ======================================================================
// Public
NX_IP ip;
NX_PACKET_POOL pool;

// Private
static TX_THREAD net_thread;
static NX_DHCP dhcp;

static NX_TELNET_SERVER telnet_srv;

/*
 * Just a note from the developper : without aligning the memory to 32 bytes
 * boundaries, the DHCP will fail more than pass, which is not really cool.
 *
 * This is due to the cache invalidation that silently fail if not properly aligned !
 */
static __aligned(32) ULONG ip_thread_stack[NX_IP_TASK_SIZE];
static __aligned(32) ULONG arp_cache[NX_ARP_CACHE / sizeof(ULONG)];
static __aligned(32) uint8_t packet_pool[PACKET_POOL_SIZE];
static __aligned(32) uint8_t net_stack[NX_MAIN_TASK_STACK];
static __aligned(32) uint8_t telnet_stack[NX_TELNET_STACK_SIZE];

// ======================================================================
//                              FUNCTIONS
// ======================================================================
// Private
static void app_network_thread_entry(ULONG arg);

// Public
UINT MX_NetXDuo_Init() {

    UINT status;

    /*
     * First, launch the nx system :
     */
    nx_system_initialize();

    /*
     * Then, create a packet pool for the incomming frames
     */
    status = nx_packet_pool_create(
        &pool, "EtherBench_Pool", NX_PACKET_SIZE, packet_pool, PACKET_POOL_SIZE);
    if (status != NX_SUCCESS)
        Error_Handler();

    /*
     * First, create an IP instance
     */
    status = nx_ip_create(
        &ip,
        "EtherBench_IP",
        IP_ADDRESS(0, 0, 0, 0), // This will say "Hey, wait for the DHCP answer !"
        IP_ADDRESS(0, 0, 0, 0),
        &pool,
        nx_stm32_eth_driver,
        (UCHAR *)ip_thread_stack,
        sizeof(ip_thread_stack),
        1);
    if (status != NX_SUCCESS)
        Error_Handler();

    /*
     * We enable the required services
     */
    status = nx_arp_enable(&ip, (VOID *)arp_cache, sizeof(arp_cache));
    if (status != NX_SUCCESS)
        Error_Handler();

    status = nx_icmp_enable(&ip);
    if (status != NX_SUCCESS)
        Error_Handler();

    status = nx_udp_enable(&ip);
    if (status != NX_SUCCESS)
        Error_Handler();

    status = nx_tcp_enable(&ip);
    if (status != NX_SUCCESS)
        Error_Handler();

    /*
     * Creating the DHCP client
     */
    status = nx_dhcp_create(&dhcp, &ip, "EtherBench_DHCP");
    if (status != NX_SUCCESS)
        Error_Handler();

    /*
     * Creating the TELNET server
     */
    status = nx_telnet_server_create(
        &telnet_srv,
        "EtherBench_Telnet",
        &ip,
        &telnet_stack,
        NX_TELNET_STACK_SIZE,
        telnet_new_connection,
        telnet_data_in,
        telnet_close_connection);

    /*
     * Finally, creating the task for the network handling.
     */
    status = tx_thread_create(
        &net_thread,
        "Network_Thread",
        app_network_thread_entry,
        0,
        net_stack,
        NX_MAIN_TASK_STACK,
        5, // Priorité (à ajuster selon votre architecture)
        5, // Preemption threshold
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    if (status != TX_SUCCESS) {
        Error_Handler();
    }

    return NX_SUCCESS;
}

void app_network_thread_entry(ULONG arg) {
    TX_PARAMETER_NOT_USED(arg);
    UINT status;
    ULONG ip_status;
    LOG("Enterred NETX application task. Will now start the required services.");

    /*
     * Wait for the link to up up. This could way for ever !
     */
    while (nx_ip_status_check(&ip, NX_IP_LINK_ENABLED, &ip_status, NX_LINK_TIMEOUT) !=
           NX_SUCCESS) {
        tx_thread_sleep(100);
        LOG("Waiting for the link to be up ...");
    }

    // Add a bit of delay, to be sure
    tx_thread_sleep(50); // 500 ms

    /*
     * Thus, we can start the DHCP server
     */
    status = nx_dhcp_start(&dhcp);
    if (status != NX_SUCCESS)
        Tx_Error_Handler(ETH_DHCP_FAILED);
    LOG("Started the DHCP client.");

    /*
     * Then, we wait until we got un IP (or timeout).
     * - Else we got a DHCP IP, and we show it into the console. That's nice and we
     *   pursuit.
     * - Or we don't, and we apply the fallback IP, and stop the DHCP.
     */
    status = nx_ip_status_check(&ip, NX_IP_ADDRESS_RESOLVED, &ip_status, NX_DHCP_TIMEOUT);

    if (status == NX_SUCCESS) {
        ULONG ip_addr;
        ULONG ip_mask;

        // Fetch the parameters
        nx_ip_address_get(&ip, &ip_addr, &ip_mask);

        LOG("Got an IP : %lu.%lu.%lu.%lu",
            (ip_addr >> 24) & 0xFF,
            (ip_addr >> 16) & 0xFF,
            (ip_addr >> 8) & 0xFF,
            (ip_addr) & 0xFF);

    } else {
        nx_dhcp_stop(&dhcp);
        nx_ip_address_set(&ip, NX_FALLBACK_IP, NX_FALLBACK_MASK);

        LOG("Used fallback IP : %lu.%lu.%lu.%lu",
            (NX_FALLBACK_IP >> 24) & 0xFF,
            (NX_FALLBACK_IP >> 16) & 0xFF,
            (NX_FALLBACK_IP >> 8) & 0xFF,
            (NX_FALLBACK_IP) & 0xFF);
    }

    /*
     * In any cases, starting the servers, as required (or secondary tasks, in that case).
     */
    status = nx_telnet_server_start(&telnet_srv);
    if (status != NX_SUCCESS)
        Tx_Error_Handler(ETH_TELNET_FAILED);
    LOG("Started Telnet server");

    /*
     * Infinite loop, to let the task active
     */
    tx_thread_suspend(tx_thread_identify());

    return;
}
