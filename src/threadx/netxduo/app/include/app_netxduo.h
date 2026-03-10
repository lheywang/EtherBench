/**
 * @file    app_netxduo.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define the main NetXDuo stack.
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

#include "nx_api.h"

// ======================================================================
//                              DEFINES
// ======================================================================

#define NX_MAIN_TASK_STACK 1024

#define NX_PACKET_SIZE 1536
#define NX_POOL_SIZE 25
#define NX_ARP_CACHE 1024
#define NX_IP_TASK_SIZE 512

#define PACKET_POOL_SIZE (NX_PACKET_SIZE * NX_POOL_SIZE)

#define NX_DHCP_TIMEOUT 6000
#define NX_LINK_TIMEOUT 10

#define NX_FALLBACK_IP IP_ADDRESS(192, 168, 1, 10)
#define NX_FALLBACK_MASK IP_ADDRESS(255, 255, 255, 0)

#define NX_TELNET_STACK_SIZE 2048

// ======================================================================
//                              VARIABLES
// ======================================================================
extern NX_IP ip;
extern NX_PACKET_POOL pool;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT MX_NetXDuo_Init();

#ifdef __cplusplus
}
#endif
