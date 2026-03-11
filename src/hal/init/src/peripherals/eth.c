/**
 * @file    eth.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Ethernet init
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "eth.h"

ETH_BufferTypeDef Txbuffer[ETH_TX_DESC_CNT * 2U];
ETH_DMADescTypeDef DMARxDscrTab[ETH_RX_DESC_CNT]; /* Ethernet Rx DMA Descriptors */
ETH_DMADescTypeDef DMATxDscrTab[ETH_TX_DESC_CNT]; /* Ethernet Tx DMA Descriptors */

// ======================================================================
//                              FUNCTIONS
// ======================================================================

ETH_HandleTypeDef heth;

/* ETH init function */
void MX_ETH_Init(void) {

    static uint8_t MACAddr[6];

    heth.Instance = ETH;
    MACAddr[0] = 0x00;
    MACAddr[1] = 0x80;
    MACAddr[2] = 0xE1;
    MACAddr[3] = 0x11;
    MACAddr[4] = 0x22;
    MACAddr[5] = 0x33;
    heth.Init.MACAddr = &MACAddr[0];
    heth.Init.MediaInterface = HAL_ETH_RMII_MODE;
    heth.Init.TxDesc = DMATxDscrTab;
    heth.Init.RxDesc = DMARxDscrTab;
    heth.Init.RxBuffLen = 1524;

    /* USER CODE BEGIN MACADDRESS */
    HAL_ETH_MspInit(&heth);

    /* USER CODE END MACADDRESS */

    if (HAL_ETH_Init(&heth) != HAL_OK) {
        Error_Handler();
    }
    return;
}

void HAL_ETH_MspInit(ETH_HandleTypeDef *ethHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (ethHandle->Instance == ETH) {

        /* ETH clock enable */
        __HAL_RCC_ETH_CLK_ENABLE();
        __HAL_RCC_ETHTX_CLK_ENABLE();
        __HAL_RCC_ETHRX_CLK_ENABLE();

        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();

        /**ETH GPIO Configuration
        PC1     ------> ETH_MDC
        PA1     ------> ETH_REF_CLK
        PA2     ------> ETH_MDIO
        PA7     ------> ETH_CRS_DV
        PC4     ------> ETH_RXD0
        PC5     ------> ETH_RXD1
        PB15     ------> ETH_TXD1
        PG11     ------> ETH_TX_EN
        PG13     ------> ETH_TXD0
        */
        GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_13;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

        /* ETH interrupt Init */
        HAL_NVIC_SetPriority(ETH_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(ETH_IRQn);
        HAL_NVIC_SetPriority(ETH_WKUP_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(ETH_WKUP_IRQn);
    }
    return;
}

void HAL_ETH_MspDeInit(ETH_HandleTypeDef *ethHandle) {

    if (ethHandle->Instance == ETH) {

        /* Peripheral clock disable */
        __HAL_RCC_ETH_CLK_DISABLE();
        __HAL_RCC_ETHTX_CLK_DISABLE();
        __HAL_RCC_ETHRX_CLK_DISABLE();

        /**ETH GPIO Configuration
        PC1     ------> ETH_MDC
        PA1     ------> ETH_REF_CLK
        PA2     ------> ETH_MDIO
        PA7     ------> ETH_CRS_DV
        PC4     ------> ETH_RXD0
        PC5     ------> ETH_RXD1
        PB15     ------> ETH_TXD1
        PG11     ------> ETH_TX_EN
        PG13     ------> ETH_TXD0
        */
        HAL_GPIO_DeInit(GPIOC, GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5);

        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_15);

        HAL_GPIO_DeInit(GPIOG, GPIO_PIN_11 | GPIO_PIN_13);

        /* ETH interrupt Deinit */
        HAL_NVIC_DisableIRQ(ETH_IRQn);
        HAL_NVIC_DisableIRQ(ETH_WKUP_IRQn);
    }
    return;
}
