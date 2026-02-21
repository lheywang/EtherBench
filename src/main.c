/**
 * @file    main.c
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Main source file for the EtherBench project.
 * @version 0.1
 * @date    2026-02-21
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "main.h"
#include "init.h"
#include "error_handler.h"

// ThreadX library
#include "app_threadx.h"

// STD
#include <stdint.h>

// ======================================================================
//                               CHECKS
// ======================================================================
// I'll let it, as a remainder, but this does not cause issues (for now ??)
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// ======================================================================
//                              MAIN APP
// ======================================================================
int main(void)
{
	// Initialize the MCU
	if (init() != HAL_OK)
		Error_Handler();

	// Launch the RTOS
	MX_ThreadX_Init();

    /*
     * We shall never get here, and, if we get, which mean critical failure,
     * we call the Error_Handler() function. (Infinite loop).
     */
	Error_Handler();
}
