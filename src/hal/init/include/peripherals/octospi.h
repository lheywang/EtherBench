/**
 * @file    octospi.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   OctoSPI init code
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

extern XSPI_HandleTypeDef hospi1;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_OCTOSPI1_Init(void);

#ifdef __cplusplus
}
#endif
