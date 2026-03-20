/**
 * @file    pka.h
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

extern PKA_HandleTypeDef hpka;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_PKA_Init(void);

#ifdef __cplusplus
}
#endif
