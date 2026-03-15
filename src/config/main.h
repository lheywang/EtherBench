/**
 * @file    main.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-15
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
#include "stm32h5xx_hal.h"

// ======================================================================
//                              DEFINES
// ======================================================================
#define BUTTON_Pin GPIO_PIN_13
#define BUTTON_GPIO_Port GPIOC
#define LED_YELLOW_Pin GPIO_PIN_4
#define LED_YELLOW_GPIO_Port GPIOF
#define LED_GREEN_Pin GPIO_PIN_0
#define LED_GREEN_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_4
#define LED_RED_GPIO_Port GPIOG

/*
 * This snipplet will force GCC to build against the timer_hal base rather than
 * the default __weak one.
 */
#define USE_TIM6_AS_HAL_TIM

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void Error_Handler(void);

#ifdef __cplusplus
}
#endif