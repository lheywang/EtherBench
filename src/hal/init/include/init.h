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

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              INCLUDES
// ======================================================================
#include <stdint.h>

// Local libraries
#include "peripherals/adc.h"
#include "peripherals/cordic.h"
#include "peripherals/dcache.h"
#include "peripherals/eth.h"
#include "peripherals/fmac.h"
#include "peripherals/gpdma.h"
#include "peripherals/gpio.h"
#include "peripherals/i2c.h"
#include "peripherals/icache.h"
#include "peripherals/rcc.h"
#include "peripherals/sdmmc.h"
#include "peripherals/spi.h"
#include "peripherals/tim.h"
#include "peripherals/usart.h"
#include "peripherals/usb.h"

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

#ifdef __cplusplus
}
#endif
