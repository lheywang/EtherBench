/**
 * @file    task_logger.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement a logger module, which handle a fast,
 * 			DMA based IO, from high level functions.
 *
 * @version 0.1
 * @date    2026-03-01
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "logger.h"

// Local library
#include "app_threadx.h"
#include "main.h"
#include "stm32h5xx_hal_uart.h"
#include "tx_api.h"

// STD
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// ======================================================================
//                              VARIABLES
// ======================================================================
/*
 * Buffer and related variables
 */
static uint8_t log_buffer[2][LOG_BUFFER_SIZE] = {{0}, {0}};
static uint32_t buffer_size[2] = {0};
static uint8_t active_buffer = 0;

/*
 * Thread management
 */
extern TX_SEMAPHORE dma_trigger;
extern TX_SEMAPHORE dma_tx_done;

/*
 * HAL
 */
extern UART_HandleTypeDef huart3;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

uint32_t add_log(const char *module, const char *file, const int line, const char *format, ...) {
    /*
     * First section : local formatting before enterring buffer handling section.
     */
    // Create a local buffer before deferring to the main pool
    uint8_t local_buffer[LOG_MAX_LENGTH];

    // Add the header to the buffer
    uint32_t header_len = snprintf((char *)local_buffer, sizeof(local_buffer), "[%s] (%s:%d) ", module, file, line);

    // Format the ##__VA_ARGS__
    va_list args;
    va_start(args, format);
    uint32_t message_len =
        vsnprintf((char *)(local_buffer + header_len), sizeof(local_buffer) - header_len, format, args);
    va_end(args);

    message_len += header_len;

    /*
     * Add a newline.
     */
    local_buffer[message_len] = '\n';
    local_buffer[message_len + 1] = '\r';
    local_buffer[message_len + 2] = '\0';
    message_len += 2;

    /*
     * Now, to ensure the logger module can work in any cases, we stop interrupt
     * to ensure no mutex are needed
     */
    UINT old_posture = tx_interrupt_control(TX_INT_DISABLE);

    uint32_t current_size = buffer_size[active_buffer];

    if ((current_size + message_len) < LOG_BUFFER_SIZE) {

        // Copy the data
        memcpy((void *)&log_buffer[active_buffer][current_size], (void *)local_buffer, (size_t)message_len);

        // Update pointer and sizes.
        buffer_size[active_buffer] += message_len;

        if ((current_size < LOG_BUFFER_THRESHOLD) && (buffer_size[active_buffer] >= LOG_BUFFER_THRESHOLD)) {
            tx_semaphore_put(&dma_trigger);
        }
    }

    tx_interrupt_control(old_posture);

    return message_len;
}

void logger_task(ULONG arg) {
    /*
     * Enterring main loop
     */

    while (1) {
        // First, wait for the semaphore. Every 250 ms, we defer all logs regardless
        // of the buffer state.
        tx_semaphore_get(&dma_trigger, 25);

        while (tx_semaphore_get(&dma_trigger, TX_NO_WAIT) == TX_SUCCESS)
            ;

        UINT old_posture = tx_interrupt_control(TX_INT_DISABLE);

        uint8_t buffer_to_send = active_buffer;
        uint32_t size_to_send = buffer_size[buffer_to_send];

        // Check is THERE IS data to send.
        if (size_to_send > 0) {

            active_buffer = 1 - active_buffer;
            buffer_size[active_buffer] = 0;

            tx_interrupt_control(old_posture);

            // Send the buffer
            if (HAL_UART_Transmit_DMA(&huart3, log_buffer[buffer_to_send], size_to_send) == HAL_OK) {
                if (tx_semaphore_get(&dma_tx_done, 200) != TX_SUCCESS) {
                    HAL_UART_AbortTransmit(&huart3);
                }
            } else {
                HAL_UART_AbortTransmit(&huart3);
            }

        } else {
            tx_interrupt_control(old_posture);
        }
    }
    return;
}

void dma_tx_callback() {
    tx_semaphore_put(&dma_tx_done);
    return;
}
