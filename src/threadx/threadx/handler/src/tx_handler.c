/**
 * @file    tx_handler.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement a common TX_handler file.
 * @version 0.1
 * @date    2026-03-04
 *
 * @copyright Copyright (c) 2026
 *
 */

// Header
#include "tx_handler.h"

// Local libraries
#include "main.h"
#include "stm32h5xx_hal.h"
#include "tx_api.h"

// STD
#include <stdint.h>

extern uint32_t add_log(
    const char *module,
    const char *file,
    const int line,
    const char *format,
    ...);

VOID Tx_Error_Handler(uint32_t error_code) {

    /*
     * First, fetch the infos about the thread
     */

    TX_THREAD *thread_ptr = tx_thread_identify();
    CHAR *thread_name = "unknown";
    UINT thread_state = 0;
    ULONG thread_run_count = 0;
    UINT thread_priority = 0;
    UINT thread_preemption = 0;
    ULONG thread_slice = 0;
    TX_THREAD *next_thread = TX_NULL;
    TX_THREAD *next_suspend = TX_NULL;

    if (thread_ptr != TX_NULL) {
        tx_thread_info_get(
            thread_ptr,
            &thread_name,
            &thread_state,
            &thread_run_count,
            &thread_priority,
            &thread_preemption,
            &thread_slice,
            &next_thread,
            &next_suspend);
    }

    /*
     * Show on the serial logger that we fetched the thread, and we won't exit
     * until here.
     */
    add_log(
        "ERROR",
        __FILE__,
        __LINE__,
        "Enterred thread %s in error state. Task can't recover until reboot. "
        "Stop code is : 0x%08x",
        thread_name,
        error_code);

    /*
     * Finally, block here until the end of time, and blink our led.
     * The delay source is selected from the current state.
     */
    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);
    for (;;) {
        HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);

        if (thread_ptr != TX_NULL) {
            tx_thread_sleep(50);
        } else {
            HAL_Delay(50);
        }
    }

    return;
}