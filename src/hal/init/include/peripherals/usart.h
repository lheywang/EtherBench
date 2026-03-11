/**
 * @file    usart.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   USART bus init code
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

extern UART_HandleTypeDef huart3;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_USART3_UART_Init(void);

#ifdef __cplusplus
}
#endif
