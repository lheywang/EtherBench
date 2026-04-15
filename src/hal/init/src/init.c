/**
 * @file    init.c
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Source file for the global MCU initialization. Depends on the ST HAL
 * library.
 * @version 0.1
 * @date    2026-02-21
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "init.h"

// Local library
#include "stm32h5xx_hal.h"

#include "adc.h"
#include "cordic.h"
#include "dcache.h"
#include "eth.h"
#include "fmac.h"
#include "gpdma.h"
#include "gpio.h"
#include "i2c.h"
#include "icache.h"
#include "rcc.h"
#include "sdmmc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb.h"

// STD
#include <stdint.h>

// ======================================================================
//                              FUNCTIONS
// ======================================================================

uint32_t init(void) {
    // Init the HAL library
    if (HAL_Init() != HAL_OK)
        return HAL_ERROR;

    // Initialize the clocks
    SystemClock_Config();

    // Initialize DMA
    MX_GPDMA1_Init();

    // Initialize Cortex M33 :
    MX_DCACHE1_Init();
    MX_ICACHE_Init();

    // Then, call the different peripherals inits :
    MX_GPIO_Init();
    MX_USART3_UART_Init();
    MX_ETH_Init();
    MX_TIM2_Init();
    MX_SDMMC1_SD_Init();

    // Computation peripherals init
    MX_CORDIC_Init();
    MX_FMAC_Init();

    return HAL_OK;
}
