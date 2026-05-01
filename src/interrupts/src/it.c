/**
 * @file    it.c
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Interrupt handler that isn't linked to the HAL, but can't be privatized to
 * 			a single file as they may be shared.
 *
 * @version 0.1
 * @date    2026-03-01
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                             INCLUDES
// ======================================================================
// Header
#include "main.h"
#include "stm32h5xx_hal.h"

// From the logger task
extern void dma_tx_callback();

// From the QSPI flash driver
extern void flash_command_complete();
extern void flash_tx_complete();
extern void flash_rx_complete();
extern void flash_polling_complete();

extern DMA_HandleTypeDef hdma_usart3_tx;          // From HAL
extern XSPI_HandleTypeDef hospi1;                 // From HAL
extern DMA_HandleTypeDef handle_GPDMA1_octospiTX; // From HAL
extern DMA_HandleTypeDef handle_GPDMA1_octospiRX; // From HAL

// ======================================================================
//                             FUNCTIONS
// ======================================================================
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    /*
     * Check which instance did trigger the interrupt
     */
    if (huart->Instance == USART3) {
        dma_tx_callback();
    }

    return;
}

void HAL_XSPI_CmdCpltCallback(XSPI_HandleTypeDef *hxspi) {
    if (hxspi->Instance == OCTOSPI1) {
        flash_command_complete();
    }
}

void HAL_XSPI_TxCpltCallback(XSPI_HandleTypeDef *hxspi) {
    if (hxspi->Instance == OCTOSPI1) {
        flash_tx_complete();
    }
}

void HAL_XSPI_RxCpltCallback(XSPI_HandleTypeDef *hxspi) {
    if (hxspi->Instance == OCTOSPI1) {
        flash_rx_complete();
    }
}

void HAL_XSPI_StatusMatchCallback(XSPI_HandleTypeDef *hxspi) {
    if (hxspi->Instance == OCTOSPI1) {
        flash_polling_complete();
    }
}

void HAL_DMA_LinkedList_CpltCallback(DMA_HandleTypeDef *hdma) {
    if (hdma == &handle_GPDMA1_octospiRX) {
        HAL_XSPI_RxCpltCallback(&hospi1);
    } else if (hdma == &handle_GPDMA1_octospiTX) {
        HAL_XSPI_ENABLE_IT(&hospi1, HAL_XSPI_IT_TC);
    }
}
