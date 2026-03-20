/**
 * @file    rng.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-20
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "rng.h"

RNG_HandleTypeDef hrng;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/* RNG init function */
void MX_RNG_Init(void) {

    hrng.Instance = RNG;
    hrng.Init.ClockErrorDetection = RNG_CED_ENABLE;
    if (HAL_RNG_Init(&hrng) != HAL_OK) {
        Error_Handler();
    }
    return;
}

void HAL_RNG_MspInit(RNG_HandleTypeDef *rngHandle) {

    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if (rngHandle->Instance == RNG) {

        /** Initializes the peripherals clock
         */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RNG;
        PeriphClkInitStruct.RngClockSelection = RCC_RNGCLKSOURCE_HSI48;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
            Error_Handler();
        }

        /* RNG clock enable */
        __HAL_RCC_RNG_CLK_ENABLE();
    }
    return;
}

void HAL_RNG_MspDeInit(RNG_HandleTypeDef *rngHandle) {

    if (rngHandle->Instance == RNG) {

        /* Peripheral clock disable */
        __HAL_RCC_RNG_CLK_DISABLE();
    }
    return;
}
