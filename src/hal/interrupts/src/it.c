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

#include "main.h"

extern void dma_tx_callback();

extern DMA_HandleTypeDef hdma_usart3_tx;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    /*
     * Check which instance did trigger the interrupt
     */
    if (huart->Instance == USART3) {
        dma_tx_callback();
    }

    return;
}

void GPDMA1_Channel0_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_usart3_tx); }
