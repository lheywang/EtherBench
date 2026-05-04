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
// Header
#include "octospi.h"

// Local libraries
#include "gpdma.h"

XSPI_HandleTypeDef hospi1;
DMA_HandleTypeDef handle_GPDMA1_octospiTX;
DMA_HandleTypeDef handle_GPDMA1_octospiRX;

// From the QSPI flash driver
extern void flash_tx_complete();
extern void flash_rx_complete();

extern void HAL_DMA_LinkedList_CpltCallback(DMA_HandleTypeDef *hdma);
extern void HAL_DMA_LinkedList_ErrorCallback(DMA_HandleTypeDef *hdma);

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_OCTOSPI1_Init(void) {

    /*
     * Configure peripheral
     */
    hospi1.Instance = OCTOSPI1;
    hospi1.Init.FifoThresholdByte = 24;
    hospi1.Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
    hospi1.Init.MemoryType = HAL_XSPI_MEMTYPE_MACRONIX;
    hospi1.Init.MemorySize = HAL_XSPI_SIZE_1GB;
    hospi1.Init.ChipSelectHighTimeCycle = 2;
    hospi1.Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
    hospi1.Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
    hospi1.Init.WrapSize = HAL_XSPI_WRAP_NOT_SUPPORTED;
    hospi1.Init.ClockPrescaler = 8;
    hospi1.Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_NONE;
    hospi1.Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_DISABLE;
    hospi1.Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_NONE;
    hospi1.Init.DelayBlockBypass = HAL_XSPI_DELAY_BLOCK_BYPASS;
    hospi1.Init.Refresh = 0;

    if (HAL_XSPI_Init(&hospi1) != HAL_OK) {
        Error_Handler();
    }

    /*
     * Configure GPDMA for the reads :
     */
    handle_GPDMA1_octospiRX.Instance = GPDMA1_Channel7;
    handle_GPDMA1_octospiRX.Mode = DMA_LINKEDLIST;
    handle_GPDMA1_octospiRX.InitLinkedList.Priority = DMA_LOW_PRIORITY_HIGH_WEIGHT;
    handle_GPDMA1_octospiRX.InitLinkedList.LinkStepMode = DMA_LSM_FULL_EXECUTION;
    handle_GPDMA1_octospiRX.InitLinkedList.LinkAllocatedPort = DMA_LINK_ALLOCATED_PORT0;
    handle_GPDMA1_octospiRX.InitLinkedList.TransferEventMode = DMA_TCEM_LAST_LL_ITEM_TRANSFER;
    handle_GPDMA1_octospiRX.InitLinkedList.LinkedListMode = DMA_LINKEDLIST_NORMAL;
    // handle_GPDMA1_octospiRX.XferCpltCallback = flash_rx_complete;
    if (HAL_DMAEx_List_Init(&handle_GPDMA1_octospiRX) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_DMA_ConfigChannelAttributes(&handle_GPDMA1_octospiRX, DMA_CHANNEL_NPRIV) != HAL_OK) {
        Error_Handler();
    }

    /*
     * Configure GPDMA for the writes :
     */

    handle_GPDMA1_octospiTX.Instance = GPDMA1_Channel6;
    handle_GPDMA1_octospiTX.Mode = DMA_LINKEDLIST;
    handle_GPDMA1_octospiTX.InitLinkedList.Priority = DMA_LOW_PRIORITY_HIGH_WEIGHT;
    handle_GPDMA1_octospiTX.InitLinkedList.LinkStepMode = DMA_LSM_FULL_EXECUTION;
    handle_GPDMA1_octospiTX.InitLinkedList.LinkAllocatedPort = DMA_LINK_ALLOCATED_PORT0;
    handle_GPDMA1_octospiTX.InitLinkedList.TransferEventMode = DMA_TCEM_LAST_LL_ITEM_TRANSFER;
    handle_GPDMA1_octospiTX.InitLinkedList.LinkedListMode = DMA_LINKEDLIST_NORMAL;
    // handle_GPDMA1_octospiTX.XferCpltCallback = flash_tx_complete;
    if (HAL_DMAEx_List_Init(&handle_GPDMA1_octospiTX) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_DMA_ConfigChannelAttributes(&handle_GPDMA1_octospiTX, DMA_CHANNEL_NPRIV) != HAL_OK) {
        Error_Handler();
    }

    __HAL_LINKDMA(&hospi1, hdmarx, handle_GPDMA1_octospiRX);
    __HAL_LINKDMA(&hospi1, hdmatx, handle_GPDMA1_octospiTX);

    /*
     * Register ISR
     */
    HAL_DMA_RegisterCallback(&handle_GPDMA1_octospiRX, HAL_DMA_XFER_CPLT_CB_ID, HAL_DMA_LinkedList_CpltCallback);
    HAL_DMA_RegisterCallback(&handle_GPDMA1_octospiTX, HAL_DMA_XFER_CPLT_CB_ID, HAL_DMA_LinkedList_CpltCallback);

    HAL_DMA_RegisterCallback(&handle_GPDMA1_octospiRX, HAL_DMA_XFER_ERROR_CB_ID, HAL_DMA_LinkedList_ErrorCallback);
    HAL_DMA_RegisterCallback(&handle_GPDMA1_octospiTX, HAL_DMA_XFER_ERROR_CB_ID, HAL_DMA_LinkedList_ErrorCallback);

    /*
     * Enable interrupts
     */
    HAL_NVIC_SetPriority(OCTOSPI1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(OCTOSPI1_IRQn);

    return;
}

/**
 * @brief The full init as QSPI is done here
 *
 * @param xspiHandle
 */
void HAL_XSPI_InitAsQSPI(XSPI_HandleTypeDef *xspiHandle) {

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
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();
        /**OCTOSPI1 GPIO Configuration
        PE2     ------> OCTOSPI1_IO2
        PB2     ------> OCTOSPI1_CLK
        PD11     ------> OCTOSPI1_IO0
        PD12     ------> OCTOSPI1_IO1
        PD13     ------> OCTOSPI1_IO3
        PG6     ------> OCTOSPI1_NCS
        */
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPI1;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPI1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPI1;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
    }
}

void HAL_XSPI_MspInit(XSPI_HandleTypeDef *xspiHandle) {

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitTypeDef GPIO_InitStruct2 = {0};
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
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_GPIOG_CLK_ENABLE();
        /**OCTOSPI1 GPIO Configuration
        PE2     ------> OCTOSPI1_IO2
        PB2     ------> OCTOSPI1_CLK
        PD11     ------> OCTOSPI1_IO0
        PD12     ------> OCTOSPI1_IO1
        PD13     ------> OCTOSPI1_IO3
        PG6     ------> OCTOSPI1_NCS
        */

        /*
         * Init only the minimal set of pins as SPI.
         */
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPI1;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF9_OCTOSPI1;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF10_OCTOSPI1;
        HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

        /*
         * The other pins are let as GPIO HIGH for now, to latch the WP and HOLD as "enabled".
         */
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);

        GPIO_InitStruct2.Pin = GPIO_PIN_13;
        GPIO_InitStruct2.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct2.Pull = GPIO_NOPULL;
        GPIO_InitStruct2.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct2);

        GPIO_InitStruct2.Pin = GPIO_PIN_2;
        GPIO_InitStruct2.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct2.Pull = GPIO_NOPULL;
        GPIO_InitStruct2.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(GPIOE, &GPIO_InitStruct2);
    }
}

void HAL_XSPI_MspDeInit(XSPI_HandleTypeDef *xspiHandle) {

    if (xspiHandle->Instance == OCTOSPI1) {

        /* Peripheral clock disable */
        __HAL_RCC_OSPI1_CLK_DISABLE();

        /**OCTOSPI1 GPIO Configuration
        PE2     ------> OCTOSPI1_IO2
        PB2     ------> OCTOSPI1_CLK
        PD11     ------> OCTOSPI1_IO0
        PD12     ------> OCTOSPI1_IO1
        PD13     ------> OCTOSPI1_IO3
        PG6     ------> OCTOSPI1_NCS
        */
        HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);

        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13);

        HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6);

        /*
         * Disable DMA
         */
        HAL_DMA_DeInit(xspiHandle->hdmarx);
        HAL_DMA_DeInit(xspiHandle->hdmatx);

        /*
         * Turn off ISR
         */
        HAL_NVIC_DisableIRQ(OCTOSPI1_IRQn);
    }
}

bool MX_OCTOSPI1_GetJEDEC() {

    XSPI_RegularCmdTypeDef sCommand = {0};
    uint8_t jedec_data[4] = {0, 0, 0, 0};

    sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
    sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction = 0x9F;
    sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
    sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
    sCommand.DataMode = HAL_XSPI_DATA_1_LINE;
    sCommand.DataLength = 4;
    sCommand.DummyCycles = 0;

    if (HAL_XSPI_Command(&hospi1, &sCommand, HAL_MAX_DELAY) != HAL_OK) {
        return HAL_ERROR;
    }

    if (HAL_XSPI_Receive(&hospi1, jedec_data, HAL_MAX_DELAY) != HAL_OK) {
        return HAL_ERROR;
    }

    if (jedec_data[0] != 0xC8) {
        return HAL_ERROR;
    }

    return HAL_OK;
}