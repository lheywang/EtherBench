/**
 * @file    telnet_bridge.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define a C / C++ friendly bridge for the NetXDuo stack
 * @version 0.1
 * @date 2026-03-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
#include <stddef.h>
#include <stdint.h>

// RTOS
#include "nxd_telnet_server.h"
#include "tx_api.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

extern "C" void telnet_push_data(const uint8_t *data, const uint32_t len);
extern "C" void telnet_connect(NX_TELNET_SERVER *server_ptr, UINT logical_connection);
extern "C" void telnet_disconnect();
