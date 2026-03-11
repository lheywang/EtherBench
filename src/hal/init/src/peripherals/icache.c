/**
 * @file    icache.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Instruction cache init
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "icache.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_ICACHE_Init(void) {

    /** Enable instruction cache (default 2-ways set associative cache)
     */
    if (HAL_ICACHE_Enable() != HAL_OK) {
        Error_Handler();
    }
    return;
}
