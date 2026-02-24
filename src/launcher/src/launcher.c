/**
 * @file    launcher.c
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Source file for the global launcher. Create and get the memory
 * 			for the different tasks.
 * @version 0.1
 * @date    2026-02-21
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "launcher.h"

// Local libraries
#include "main.h"
#include "idle.h"

// ThreadX library
#include "app_threadx.h"
#include "app_usbx_device.h"

// STD
#include <stdint.h>

// ======================================================================
//                              MEMORY AREAS
// ======================================================================
TX_THREAD idle_thread;
uint8_t idle_stack[IDLE_STACK_SIZE];

// ======================================================================
//                              FUNCTIONS
// ======================================================================

uint32_t launcher(void)
{

	/*
	 * Launching the USBX task
	 */
    MX_USBX_Device_Init();

	/*
	 * Creating the idle task
	 */
	tx_thread_create(
			&idle_thread,
			"Idle blink",
			idle_task,
			0,
			idle_stack,
			IDLE_STACK_SIZE,
	        31,
			31,
			TX_NO_TIME_SLICE,
			TX_AUTO_START
	);
    return 0;
}

