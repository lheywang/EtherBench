/**
 * @file    cordic.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Cordic init
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "cordic.h"
extern void Error_Handler();

CORDIC_HandleTypeDef hcordic;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_CORDIC_Init(void) {

    hcordic.Instance = CORDIC;
    if (HAL_CORDIC_Init(&hcordic) != HAL_OK) {
        Error_Handler();
    }

    return;
}

void HAL_CORDIC_MspInit(CORDIC_HandleTypeDef *cordicHandle) {

    if (cordicHandle->Instance == CORDIC) {
        /* CORDIC clock enable */
        __HAL_RCC_CORDIC_CLK_ENABLE();
    }

    return;
}

void HAL_CORDIC_MspDeInit(CORDIC_HandleTypeDef *cordicHandle) {

    if (cordicHandle->Instance == CORDIC) {
        /* Peripheral clock disable */
        __HAL_RCC_CORDIC_CLK_DISABLE();
    }

    return;
}
