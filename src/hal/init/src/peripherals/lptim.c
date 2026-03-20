/**
 * @file    lptim.c
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
#include "lptim.h"

LPTIM_HandleTypeDef hlptim5;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/* LPTIM5 init function */
void MX_LPTIM5_Init(void) {

    hlptim5.Instance = LPTIM5;
    hlptim5.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
    hlptim5.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV1;
    hlptim5.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
    hlptim5.Init.Period = 65535;
    hlptim5.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
    hlptim5.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
    hlptim5.Init.Input1Source = LPTIM_INPUT1SOURCE_GPIO;
    hlptim5.Init.Input2Source = LPTIM_INPUT2SOURCE_GPIO;
    hlptim5.Init.RepetitionCounter = 0;
    if (HAL_LPTIM_Init(&hlptim5) != HAL_OK) {
        Error_Handler();
    }
    return;
}

void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef *lptimHandle) {

    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if (lptimHandle->Instance == LPTIM5) {

        /** Initializes the peripherals clock
         */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LPTIM5;
        PeriphClkInitStruct.Lptim5ClockSelection = RCC_LPTIM5CLKSOURCE_PCLK3;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
            Error_Handler();
        }

        /* LPTIM5 clock enable */
        __HAL_RCC_LPTIM5_CLK_ENABLE();
    }
    return;
}

void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef *lptimHandle) {

    if (lptimHandle->Instance == LPTIM5) {
        /* Peripheral clock disable */
        __HAL_RCC_LPTIM5_CLK_DISABLE();
    }
    return;
}
