/**
 * @file    logger.h
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Header to define the base a logger module, which handle a fast,
 * 			DMA based IO, from high level functions.
 *
 * @version 0.1
 * @date    2026-03-01
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
#include "logger.h"

// STD
#include <stdint.h>

// ======================================================================
//                              DEFINES
// ======================================================================

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void parser_task(ULONG arg);

#ifdef __cplusplus
}
#endif
