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
#include "error_handler.h"
#include "init.h"

// STD
#include <stdint.h>

// ThreadX
#include "app_threadx.h"

// ======================================================================
//                              MAIN APP
// ======================================================================
int main(void) {
    // Initialize the MCU (peripheral only)
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
