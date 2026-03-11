/**
 * @file    gpdma.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   General purpose DMA init code
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

extern DMA_HandleTypeDef hdma_usart3_tx;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_GPDMA2_Init(void);
void MX_GPDMA1_Init(void);

#ifdef __cplusplus
}
#endif
