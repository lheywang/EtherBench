/**
 * @file    sdmmc.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   SDMMC bus init code
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

extern SD_HandleTypeDef hsd1;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_SDMMC1_SD_Init(void);

#ifdef __cplusplus
}
#endif
