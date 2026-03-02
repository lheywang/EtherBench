/**
 * @file    init.h
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Header file for the global MCU initialization. Depends on the ST HAL library.
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
#include <stdint.h>

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/**
 * @brief   Init the system with the parameters defined into the functions,
 *          and the default values defined into the ST HAL library, by
 *          CubeMX.
 *
 * @return uint32_t
 */
uint32_t init(void);
