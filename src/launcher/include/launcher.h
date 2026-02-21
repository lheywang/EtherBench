/**
 * @file    launcher.c
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Header file for the global launcher. Create the tasks and
 * 			memory regions.
 * @version 0.1
 * @date    2026-02-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// STD
#include <stdint.h>

// ======================================================================
//                              DEFINES
// ======================================================================
#define IDLE_STACK_SIZE 1024

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/**
 * @brief 	This function is charged to initialize the memory areas and
 * 			launch the different tasks needed.
 *
 * 			This enable to perform a clear separation of the kernel space,
 * 			and the user space.
 *
 * 			Automatically called from tx_application_define from the
 * 			threadX init procedure.
 *
 * @return	uint32_t status.
 */
uint32_t launcher(void);

