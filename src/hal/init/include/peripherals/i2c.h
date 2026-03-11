/**
 * @file    i2c.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   I2C init code
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

extern I2C_HandleTypeDef hi2c1;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_I2C1_Init(void);

#ifdef __cplusplus
}
#endif
