/**
 * @file    fmac.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   FMAC init
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "fmac.h"

FMAC_HandleTypeDef hfmac;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_FMAC_Init(void) {

    hfmac.Instance = FMAC;
    if (HAL_FMAC_Init(&hfmac) != HAL_OK) {
        Error_Handler();
    }
    return;
}

void HAL_FMAC_MspInit(FMAC_HandleTypeDef *fmacHandle) {

    if (fmacHandle->Instance == FMAC) {

        /* FMAC clock enable */
        __HAL_RCC_FMAC_CLK_ENABLE();
    }
    return;
}

void HAL_FMAC_MspDeInit(FMAC_HandleTypeDef *fmacHandle) {

    if (fmacHandle->Instance == FMAC) {

        /* Peripheral clock disable */
        __HAL_RCC_FMAC_CLK_DISABLE();
    }
    return;
}
