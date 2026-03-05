/**
 * @file    app_netxduo_status.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define callbacks used by the netxduo stack.
 * @version 0.1
 * @date    2026-03-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              INCLUDES
// ======================================================================

// NetXDuo
#include "nx_api.h"

// Addons
#include "nxd_telnet_server.h"

// ======================================================================
//                              VARIABLES
// ======================================================================

// ======================================================================
//                              FUNCTIONS
// ======================================================================

VOID telnet_new_connection(NX_TELNET_SERVER *server_ptr, UINT logical_connection);
void telnet_data_in(
    NX_TELNET_SERVER *server_ptr, UINT logical_connection, NX_PACKET *packet_ptr);
void telnet_close_connection(NX_TELNET_SERVER *server_ptr, UINT logical_connection);

#ifdef __cplusplus
}
#endif
