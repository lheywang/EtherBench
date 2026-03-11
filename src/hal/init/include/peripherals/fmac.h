/**
 * @file    fmac.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
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

extern FMAC_HandleTypeDef hfmac;

// ======================================================================
//                              FUNCTIONS
// ======================================================================
void MX_FMAC_Init(void);

#ifdef __cplusplus
}
#endif
