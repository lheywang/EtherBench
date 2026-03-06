/**
 * @file    telnet_bridge.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   C / C++ bridge for the USB stack
 * @version 0.1
 * @date    2026-03-06
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "bridge/telnet_bridge.h"

// Class
#include "ShellStream/ShellStreamTelnet.hpp"

// ======================================================================
//                              VARIABLES
// ======================================================================
static uint8_t telnet_buffer[SHELL_LINE_LENGTH];

extern NX_PACKET_POOL pool;

ShellStreamTelnet telnet_stream(&pool, (char *)telnet_buffer, sizeof(telnet_buffer));

// ======================================================================
//                              FUNCTIONS
// ======================================================================

extern "C" void telnet_push_data(const uint8_t *data, const uint32_t len) {
    // Check if data is OK.
    if (!data || len == 0)
        return;

    // Process the data.
    telnet_stream.process((const char *)data, len);
    return;
}

extern "C" void telnet_connect(NX_TELNET_SERVER *server_ptr, UINT logical_connection) {
    telnet_stream.connect(server_ptr, logical_connection);
    return;
}

extern "C" void telnet_disconnect() {
    telnet_stream.disconnect();
    return;
}