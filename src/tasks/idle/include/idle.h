/**
 * @file    idle.h
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Header file for most simple task, a blinking led, to show
 * 			the system hasn't crashed (yet ?)
 * @version 0.1
 * @date    2026-02-21
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local library
#include "app_threadx.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void idle_task(ULONG arg);

#ifdef __cplusplus
}
#endif

