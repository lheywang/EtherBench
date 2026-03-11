/**
 * @file    cordic.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Cordic peripheral init
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

extern CORDIC_HandleTypeDef hcordic;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_CORDIC_Init(void);

#ifdef __cplusplus
}
#endif
