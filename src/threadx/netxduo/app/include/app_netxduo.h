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

#define NX_PACKET_SIZE 1536
#define NX_POOL_SIZE 10
#define NX_ARP_CACHE 1024
#define NX_IP_TASK_SIZE 512

#define PACKET_POOL_SIZE (NX_PACKET_SIZE * NX_POOL_SIZE)

// ======================================================================
//                              VARIABLES
// ======================================================================

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT MX_NetXDuo_Init();

#ifdef __cplusplus
}
#endif
