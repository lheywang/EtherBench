/**
 * @file    ShellStreamTelnet.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-06
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
// Header
#include "ShellStream/ShellStreamTelnet.hpp"

// RTOS
#include "nxd_telnet_server.h"
#include "tx_api.h"

// ======================================================================
//                            CLASS IMPL
// ======================================================================

void ShellStreamTelnet::hw_transmit(const char *data, size_t length) {
    if (instance) {
        if (!instance || !data || length == 0) {
            return;
        }

        NX_PACKET *packet_ptr;
        UINT status;

        status = nx_packet_allocate(packet_pool, &packet_ptr, NX_TCP_PACKET, NX_NO_WAIT);

        if (status != NX_SUCCESS) {
            return;
        }

        status = nx_packet_data_append(
            packet_ptr, (VOID *)data, length, packet_pool, NX_NO_WAIT);

        if (status != NX_SUCCESS) {
            nx_packet_release(packet_ptr);
            return;
        }

        status = nx_telnet_server_packet_send(
            instance, logical_connection, packet_ptr, NX_NO_WAIT);

        if (status != NX_SUCCESS) {
            nx_packet_release(packet_ptr);
        }
    }
    return;
}

void ShellStreamTelnet::connect(NX_TELNET_SERVER *instance, UINT logical_connection) {
    this->instance = instance;
    this->logical_connection = logical_connection;
    return;
}

void ShellStreamTelnet::disconnect() {
    this->instance = nullptr;
    this->logical_connection = -1;
    return;
}
