/**
 * @file    dcache.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Data cache init
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================

#include "dcache.h"

DCACHE_HandleTypeDef hdcache1;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_DCACHE1_Init(void) {

    hdcache1.Instance = DCACHE1;
    hdcache1.Init.ReadBurstType = DCACHE_READ_BURST_WRAP;
    if (HAL_DCACHE_Init(&hdcache1) != HAL_OK) {
        Error_Handler();
    }
    return;
}

void HAL_DCACHE_MspInit(DCACHE_HandleTypeDef *dcacheHandle) {

    if (dcacheHandle->Instance == DCACHE1) {
        /* DCACHE1 clock enable */
        __HAL_RCC_DCACHE1_CLK_ENABLE();
    }
    return;
}

void HAL_DCACHE_MspDeInit(DCACHE_HandleTypeDef *dcacheHandle) {

    if (dcacheHandle->Instance == DCACHE1) {
        /* Peripheral clock disable */
        __HAL_RCC_DCACHE1_CLK_DISABLE();
    }
    return;
}
