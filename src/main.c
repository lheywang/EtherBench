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

// STD
#include <stdint.h>

// ======================================================================
//                               CHECKS
// ======================================================================


// ======================================================================
//                              MAIN APP
// ======================================================================
int main(void)
{
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#ifndef INIT_FPU
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#else
#pragma message "Initialized FPU"
	SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2)); // Full access for CP10 and CP11
	__DSB(); // Ensure complete set up before proceeding
	__ISB();
#endif /* INIT_FPU */
#endif /* !defined(__SOFT_FP__) && defined(__ARM_FP) */

	// Init the MCU
	init();

    /* Loop forever */
	for(;;)
	{
		HAL_Delay(500);
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	}
}
