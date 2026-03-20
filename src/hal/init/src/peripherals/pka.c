/**
 * @file    pka.c
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
#include "pka.h"

PKA_HandleTypeDef hpka;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/* PKA init function */
void MX_PKA_Init(void) {

    hpka.Instance = PKA;
    if (HAL_PKA_Init(&hpka) != HAL_OK) {
        Error_Handler();
    }
    return;
}

void HAL_PKA_MspInit(PKA_HandleTypeDef *pkaHandle) {

    if (pkaHandle->Instance == PKA) {
        /* PKA clock enable */
        __HAL_RCC_PKA_CLK_ENABLE();
    }
    return;
}

void HAL_PKA_MspDeInit(PKA_HandleTypeDef *pkaHandle) {

    if (pkaHandle->Instance == PKA) {
        /* Peripheral clock disable */
        __HAL_RCC_PKA_CLK_DISABLE();
    }
    return;
}
