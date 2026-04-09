/**
 * @file    octospi.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   OctoSPI init
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "octospi.h"
extern void Error_Handler();

XSPI_HandleTypeDef hospi1;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_OCTOSPI1_Init(void) {

    hospi1.Instance = OCTOSPI1;
    hospi1.Init.FifoThresholdByte = 1;
    hospi1.Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
    hospi1.Init.MemoryType = HAL_XSPI_MEMTYPE_MICRON;
    hospi1.Init.MemorySize = HAL_XSPI_SIZE_16B;
    hospi1.Init.ChipSelectHighTimeCycle = 1;
    hospi1.Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
    hospi1.Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
    hospi1.Init.WrapSize = HAL_XSPI_WRAP_NOT_SUPPORTED;
    hospi1.Init.ClockPrescaler = 0;
    hospi1.Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_NONE;
    hospi1.Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_DISABLE;
    hospi1.Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_NONE;
    hospi1.Init.DelayBlockBypass = HAL_XSPI_DELAY_BLOCK_BYPASS;
    hospi1.Init.Refresh = 0;
    if (HAL_XSPI_Init(&hospi1) != HAL_OK) {
        Error_Handler();
    }
    return;
}

void HAL_XSPI_MspInit(XSPI_HandleTypeDef *xspiHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    if (xspiHandle->Instance == OCTOSPI1) {

        /** Initializes the peripherals clock
         */
        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
        PeriphClkInitStruct.OspiClockSelection = RCC_OSPICLKSOURCE_HCLK;
        if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
            Error_Handler();
        }

        /* OCTOSPI1 clock enable */
        __HAL_RCC_OSPI1_CLK_ENABLE();

        __HAL_RCC_GPIOE_CLK_ENABLE();
        __HAL_RCC_GPIOF_CLK_ENABLE();
        /**OCTOSPI1 GPIO Configuration
        PE2     ------> OCTOSPI1_IO2
        PF6     ------> OCTOSPI1_IO3
        PF8     ------> OCTOSPI1_IO0
        PF9     ------> OCTOSPI1_IO1
        PF10     ------> OCTOSPI1_CLK
        PE11     ------> OCTOSPI1_NCS
        */
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPI1;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPI1;
        HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF6_OCTOSPI1;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    }
    return;
}

void HAL_XSPI_MspDeInit(XSPI_HandleTypeDef *xspiHandle) {

    if (xspiHandle->Instance == OCTOSPI1) {

        /* Peripheral clock disable */
        __HAL_RCC_OSPI1_CLK_DISABLE();

        /**OCTOSPI1 GPIO Configuration
        PE2     ------> OCTOSPI1_IO2
        PF6     ------> OCTOSPI1_IO3
        PF8     ------> OCTOSPI1_IO0
        PF9     ------> OCTOSPI1_IO1
        PF10     ------> OCTOSPI1_CLK
        PE11     ------> OCTOSPI1_NCS
        */
        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2 | GPIO_PIN_11);

        HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10);
    }
    return;
}
