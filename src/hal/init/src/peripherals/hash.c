/**
 * @file    hash.c
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
#include "hash.h"

HASH_HandleTypeDef hhash;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/* HASH init function */
void MX_HASH_Init(void) {

    hhash.Instance = HASH;
    hhash.Init.DataType = HASH_NO_SWAP;
    hhash.Init.Algorithm = HASH_ALGOSELECTION_SHA1;
    if (HAL_HASH_Init(&hhash) != HAL_OK) {
        Error_Handler();
    }
}

void HAL_HASH_MspInit(HASH_HandleTypeDef *hashHandle) {

    /* HASH clock enable */
    __HAL_RCC_HASH_CLK_ENABLE();
    return;
}

void HAL_HASH_MspDeInit(HASH_HandleTypeDef *hashHandle) {

    /* Peripheral clock disable */
    __HAL_RCC_HASH_CLK_DISABLE();
    return;
}
