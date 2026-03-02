/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gpdma.h
 * @brief   This file contains all the function prototypes for
 *          the gpdma.c file
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
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPDMA_H__
#define __GPDMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

extern DMA_HandleTypeDef hdma_usart3_tx;

void MX_GPDMA2_Init(void);
void MX_GPDMA1_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPDMA_H__ */
