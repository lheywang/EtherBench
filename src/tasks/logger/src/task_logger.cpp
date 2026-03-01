/**
 * @file    logger.h
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Header to define the base a logger module, which handle a fast,
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

// STD
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// ======================================================================
//                              VARIABLES
// ======================================================================
/*
 * Buffer and related variables
 */
static uint8_t log_buffer[LOG_BUFFER_SIZE] = {0};
static uint8_t *head = &log_buffer[0];
static uint32_t buffer_size = 0;
static uint8_t tx_process = 0;

/*
 * Thread management
 */
TX_SEMAPHORE dma_trigger;

/*
 * HAL
 */
extern UART_HandleTypeDef huart3;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

uint32_t add_log(const char *module, const char* file, const int line, const char * format, ...)
{
	/*
	 * Wait if there's a TX in progres, to not corrupt the data.
	 */
	while (tx_process == 1) {}
	/*
	 * First section : local formatting before enterring buffer handling section.
	 */
	// Create a local buffer before deferring to the main pool
	uint8_t local_buffer[LOG_MAX_LENGTH];

	// Add the header to the buffer
	uint32_t header_len = snprintf((char *)local_buffer, sizeof(local_buffer), "[%s] (%s%3d)", module, file, line);

	// Format the ##__VA_ARGS__
	va_list args;
	va_start(args, format);
	uint32_t message_len = vsnprintf((char *)(local_buffer + header_len), sizeof(local_buffer) - header_len, format, args);
	va_end(args);

	message_len += header_len;

	/*
	 * Now, to ensure the logger module can work in any cases, we stop interrupt to ensure no mutex are needed
	 */
	UINT old_posture = tx_interrupt_control(TX_INT_DISABLE);

	buffer_size += message_len;
	memcpy((void *)head, (void*)local_buffer, message_len);

	tx_interrupt_control(old_posture);

	/*
	 * Finish by setting up flags and others elements
	 */
	if (buffer_size > LOG_BUFFER_THRESHOLD)
	{
		tx_semaphore_put(&dma_trigger);
	}

	return message_len;
}

void logger_task(ULONG arg)
{
	/*
	 * Enterring main loop
	 */
	while (1)
	{
		// First, wait for the semaphore. Every 250 ms, we defer all logs regardless of the buffer state.
		tx_semaphore_get(&dma_trigger, 25);
		if (tx_process == 0)
		{
			tx_process = 1;

			// Send the buffer
			HAL_UART_Transmit_DMA(&huart3, log_buffer, buffer_size);
		}
	}

	return;

}

void dma_tx_callback()
{
	/*
	 * Clean the buffer and restore variables.
	 */
	memset((void *)log_buffer, 0x00, (size_t)sizeof(log_buffer));
	buffer_size = 0;
	head = &log_buffer[0];
	tx_process = 0;
	return;
}
