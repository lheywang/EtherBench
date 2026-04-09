/**
 * @file    tim.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Timer init code
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "tim.h"
extern void Error_Handler();

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
DMA_HandleTypeDef handle_GPDMA1_Channel1;
DMA_HandleTypeDef handle_GPDMA2_Channel0;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_TIM1_Init(void) {

    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 0;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 312;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 104;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) {
        Error_Handler();
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.BreakFilter = 0;
    sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
    sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
    sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
    sBreakDeadTimeConfig.Break2Filter = 0;
    sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK) {
        Error_Handler();
    }

    HAL_TIM_MspPostInit(&htim1);
    return;
}

void MX_TIM2_Init(void) {

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 0;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 311;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 156;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) {
        Error_Handler();
    }

    HAL_TIM_MspPostInit(&htim2);
    return;
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *tim_pwmHandle) {

    if (tim_pwmHandle->Instance == TIM1) {

        /* TIM1 clock enable */
        __HAL_RCC_TIM1_CLK_ENABLE();

        /* TIM1 DMA Init */
        /* GPDMA1_REQUEST_TIM1_CH2 Init */
        handle_GPDMA1_Channel1.Instance = GPDMA1_Channel1;
        handle_GPDMA1_Channel1.Init.Request = GPDMA1_REQUEST_TIM1_CH2;
        handle_GPDMA1_Channel1.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
        handle_GPDMA1_Channel1.Init.Direction = DMA_MEMORY_TO_PERIPH;
        handle_GPDMA1_Channel1.Init.SrcInc = DMA_SINC_INCREMENTED;
        handle_GPDMA1_Channel1.Init.DestInc = DMA_DINC_FIXED;
        handle_GPDMA1_Channel1.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_HALFWORD;
        handle_GPDMA1_Channel1.Init.DestDataWidth = DMA_DEST_DATAWIDTH_BYTE;
        handle_GPDMA1_Channel1.Init.Priority = DMA_LOW_PRIORITY_LOW_WEIGHT;
        handle_GPDMA1_Channel1.Init.SrcBurstLength = 1;
        handle_GPDMA1_Channel1.Init.DestBurstLength = 1;
        handle_GPDMA1_Channel1.Init.TransferAllocatedPort =
            DMA_SRC_ALLOCATED_PORT1 | DMA_DEST_ALLOCATED_PORT1;
        handle_GPDMA1_Channel1.Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
        handle_GPDMA1_Channel1.Init.Mode = DMA_NORMAL;
        if (HAL_DMA_Init(&handle_GPDMA1_Channel1) != HAL_OK) {
            Error_Handler();
        }

        __HAL_LINKDMA(tim_pwmHandle, hdma[TIM_DMA_ID_CC2], handle_GPDMA1_Channel1);

        if (HAL_DMA_ConfigChannelAttributes(&handle_GPDMA1_Channel1, DMA_CHANNEL_NPRIV) !=
            HAL_OK) {
            Error_Handler();
        }
    }
    return;
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *tim_baseHandle) {

    if (tim_baseHandle->Instance == TIM2) {

        /* TIM2 clock enable */
        __HAL_RCC_TIM2_CLK_ENABLE();

        /* TIM2 DMA Init */
        /* GPDMA2_REQUEST_TIM2_CH1 Init */
        handle_GPDMA2_Channel0.Instance = GPDMA2_Channel0;
        handle_GPDMA2_Channel0.Init.Request = GPDMA2_REQUEST_TIM2_CH1;
        handle_GPDMA2_Channel0.Init.BlkHWRequest = DMA_BREQ_SINGLE_BURST;
        handle_GPDMA2_Channel0.Init.Direction = DMA_MEMORY_TO_PERIPH;
        handle_GPDMA2_Channel0.Init.SrcInc = DMA_SINC_INCREMENTED;
        handle_GPDMA2_Channel0.Init.DestInc = DMA_DINC_FIXED;
        handle_GPDMA2_Channel0.Init.SrcDataWidth = DMA_SRC_DATAWIDTH_HALFWORD;
        handle_GPDMA2_Channel0.Init.DestDataWidth = DMA_DEST_DATAWIDTH_HALFWORD;
        handle_GPDMA2_Channel0.Init.Priority = DMA_LOW_PRIORITY_LOW_WEIGHT;
        handle_GPDMA2_Channel0.Init.SrcBurstLength = 1;
        handle_GPDMA2_Channel0.Init.DestBurstLength = 1;
        handle_GPDMA2_Channel0.Init.TransferAllocatedPort =
            DMA_SRC_ALLOCATED_PORT0 | DMA_DEST_ALLOCATED_PORT0;
        handle_GPDMA2_Channel0.Init.TransferEventMode = DMA_TCEM_BLOCK_TRANSFER;
        handle_GPDMA2_Channel0.Init.Mode = DMA_NORMAL;
        if (HAL_DMA_Init(&handle_GPDMA2_Channel0) != HAL_OK) {
            Error_Handler();
        }

        __HAL_LINKDMA(tim_baseHandle, hdma[TIM_DMA_ID_CC1], handle_GPDMA2_Channel0);

        if (HAL_DMA_ConfigChannelAttributes(&handle_GPDMA2_Channel0, DMA_CHANNEL_NPRIV) !=
            HAL_OK) {
            Error_Handler();
        }
    }
    return;
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *timHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (timHandle->Instance == TIM1) {

        __HAL_RCC_GPIOE_CLK_ENABLE();
        /**TIM1 GPIO Configuration
        PE11     ------> TIM1_CH2
        */
        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    } else if (timHandle->Instance == TIM2) {

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**TIM2 GPIO Configuration
        PA0     ------> TIM2_CH1
        */
        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    return;
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *tim_pwmHandle) {

    if (tim_pwmHandle->Instance == TIM1) {

        /* Peripheral clock disable */
        __HAL_RCC_TIM1_CLK_DISABLE();

        /* TIM1 DMA DeInit */
        HAL_DMA_DeInit(tim_pwmHandle->hdma[TIM_DMA_ID_CC2]);
    }
    return;
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *tim_baseHandle) {

    if (tim_baseHandle->Instance == TIM2) {

        /* Peripheral clock disable */
        __HAL_RCC_TIM2_CLK_DISABLE();

        /* TIM2 DMA DeInit */
        HAL_DMA_DeInit(tim_baseHandle->hdma[TIM_DMA_ID_CC1]);
    }
    return;
}
