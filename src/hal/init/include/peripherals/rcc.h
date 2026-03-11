/**
 * @file    rcc.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Clocks init code
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              INCLUDE
// ======================================================================
#include "main.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif
