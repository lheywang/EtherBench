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

extern TIM_HandleTypeDef htim2;
extern DCACHE_HandleTypeDef hdcache1;
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

    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 156);

    // HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

#define CCRValue_BufferSize 24

    ALIGN_32BYTES(uint32_t DiscontinuousSineCCRValue_Buffer[CCRValue_BufferSize]) = {
        208, 208, 208, 208, 208, 208, 208, 208, 104, 104, 104, 104,
        104, 104, 104, 104, 208, 208, 208, 208, 208, 208, 208, 208};

    HAL_DCACHE_InvalidateByAddr(
        &hdcache1,
        DiscontinuousSineCCRValue_Buffer,
        sizeof(DiscontinuousSineCCRValue_Buffer));

    HAL_TIM_PWM_Start_DMA(
        &htim2, TIM_CHANNEL_1, DiscontinuousSineCCRValue_Buffer, CCRValue_BufferSize);

    // Computation peripherals init
    MX_CORDIC_Init();
    MX_FMAC_Init();

    return HAL_OK;
}
