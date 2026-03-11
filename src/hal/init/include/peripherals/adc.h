/**
 * @file    adc.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Init code for the ADC
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
//                              INCLUDES
// ======================================================================
#include "main.h"

extern ADC_HandleTypeDef hadc1;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_ADC1_Init(void);

#ifdef __cplusplus
}
#endif
