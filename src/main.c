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

// STD
#include <stdint.h>

// ======================================================================
//                               CHECKS
// ======================================================================
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


// ======================================================================
//                              MAIN APP
// ======================================================================
int main(void)
{

	// Init the MCU
	if (init() != HAL_OK)
		Error_Handler();

    /* Loop forever */
	for(;;)
	{
		HAL_Delay(500);
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
	}
}
