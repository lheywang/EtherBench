
/**
 ******************************************************************************
 * @file    gpdma.c
 * @brief   This file provides code for the configuration
 *          of the GPDMA instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gpdma.h"
#include "stm32h563xx.h"
#include "stm32h5xx_hal_dma.h"

#include <string.h>

DMA_HandleTypeDef hdma_usart3_tx;

void MX_GPDMA1_Init(void) {

    /* Peripheral clock enable */
    __HAL_RCC_GPDMA1_CLK_ENABLE();

    /* GPDMA2 interrupt Init */
    HAL_NVIC_SetPriority(GPDMA1_Channel0_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(GPDMA1_Channel0_IRQn);
}

void MX_GPDMA2_Init(void) {

    /* Peripheral clock enable */
    __HAL_RCC_GPDMA2_CLK_ENABLE();

    /* GPDMA2 interrupt Init */
    // HAL_NVIC_SetPriority(GPDMA2_Channel0_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(GPDMA2_Channel0_IRQn);
}
