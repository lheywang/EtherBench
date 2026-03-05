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

// NetXDuo
#include "nx_api.h"

// ======================================================================
//                               EXTERNS
// ======================================================================

extern void Error_Handler();

// ======================================================================
//                              VARIABLES
// ======================================================================
// Public

// Private
static NX_PACKET_POOL pool;
static NX_IP ip;

static __aligned(8) ULONG ip_thread_stack[NX_IP_TASK_SIZE];
static __aligned(8) ULONG arp_cache[NX_ARP_CACHE / sizeof(ULONG)];

static __aligned(8) uint8_t packet_pool[PACKET_POOL_SIZE];

// ======================================================================
//                              FUNCTIONS
// ======================================================================

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
    LOG("Created the packet pool.");

    /*
     * First, create an IP instance
     */
    status = nx_ip_create(
        &ip,
        "EtherBench_IP",
        IP_ADDRESS(192, 168, 1, 10),
        IP_ADDRESS(255, 255, 255, 0),
        &pool,
        nx_stm32_eth_driver,
        (UCHAR *)ip_thread_stack,
        sizeof(ip_thread_stack),
        1);
    if (status != NX_SUCCESS)
        Error_Handler();
    LOG("Created the IP task.");

    /*
     * We enable the required services
     */
    status = nx_arp_enable(&ip, (VOID *)arp_cache, sizeof(arp_cache));
    if (status != NX_SUCCESS)
        Error_Handler();
    LOG("Enabled the ARP protocol.");

    status = nx_icmp_enable(&ip);
    if (status != NX_SUCCESS)
        Error_Handler();
    LOG("Enabled the ICMP protocol.");

    return NX_SUCCESS;
}
