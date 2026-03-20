/**
 * @file    lptim.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-20
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

extern LPTIM_HandleTypeDef hlptim5;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_LPTIM5_Init(void);

#ifdef __cplusplus
}
#endif
