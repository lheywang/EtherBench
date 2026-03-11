/**
 * @file    dcache.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Data cache init
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "main.h"

extern DCACHE_HandleTypeDef hdcache1;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_DCACHE1_Init(void);

#ifdef __cplusplus
}
#endif
