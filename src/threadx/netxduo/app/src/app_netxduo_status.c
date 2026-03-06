/**
 * @file    app_netxduo_status.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement callbacks from the NetXDuo stack.
 * @version 0.1
 * @date    2026-03-05
 *
 * @copyright Copyright (c) 2026
 *
 */

// Just a quick logger config
#define LOG_MODULE "NETX_STATUS"

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "app_netxduo_status.h"

// Local libraries
#include "logger.h"
#include "nx_api.h"

extern void telnet_push_data(const uint8_t *data, const uint32_t len);
extern void telnet_connect(NX_TELNET_SERVER *server_ptr, UINT logical_connection);
extern void telnet_disconnect();

// ======================================================================
//                              VARIABLES
// ======================================================================

extern NX_IP ip;
extern NX_PACKET_POOL pool;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

VOID telnet_new_connection(NX_TELNET_SERVER *server_ptr, UINT logical_connection) {
    NX_PACKET *response_packet;

    // Create a welcome packet.
    nx_packet_allocate(&pool, &response_packet, NX_TCP_PACKET, NX_NO_WAIT);
    nx_packet_data_append(
        response_packet,
        "Welcome to EtherBench CLI!\r\nEtherBench> ",
        38,
        &pool,
        NX_NO_WAIT);

    // Send the packet to the client.
    nx_telnet_server_packet_send(
        server_ptr, logical_connection, response_packet, NX_WAIT_FOREVER);

    // Connect the stream handle
    telnet_connect(server_ptr, logical_connection);

    return;
}

void telnet_data_in(
    NX_TELNET_SERVER *server_ptr, UINT logical_connection, NX_PACKET *packet_ptr) {

    packet_ptr->nx_packet_append_ptr[0] = '\0';

    char *cmd_string = (char *)packet_ptr->nx_packet_prepend_ptr;
    LOG("Command received: %s", cmd_string);

    // Add the data to the parser.
    telnet_push_data(
        (uint8_t *)packet_ptr->nx_packet_prepend_ptr,
        (uint32_t)packet_ptr->nx_packet_length);

    nx_packet_release(packet_ptr);

    return;
}

void telnet_close_connection(NX_TELNET_SERVER *server_ptr, UINT logical_connection) {
    LOG("Telnet client disconnected.");

    // Close the stream handle
    telnet_disconnect();

    return;
}
