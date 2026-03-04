/**
 * @file    app_usbx_device.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-04
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

#include "app_azure_rtos_config.h"
#include "ux_api.h"
#include "ux_dcd_stm32.h"

// ======================================================================
//                              DEFINES
// ======================================================================

#define USBX_DEVICE_MEMORY_STACK_SIZE 512

#define UX_DEVICE_APP_THREAD_STACK_SIZE 2048
#define UX_SYSTEM_MEM_SIZE 32768
#define UX_DEVICE_APP_THREAD_PRIO 10

#ifndef UX_DEVICE_APP_THREAD_NAME
#define UX_DEVICE_APP_THREAD_NAME "USBX Device App Main Thread"
#endif

#ifndef UX_DEVICE_APP_THREAD_PREEMPTION_THRESHOLD
#define UX_DEVICE_APP_THREAD_PREEMPTION_THRESHOLD UX_DEVICE_APP_THREAD_PRIO
#endif

#ifndef UX_DEVICE_APP_THREAD_TIME_SLICE
#define UX_DEVICE_APP_THREAD_TIME_SLICE TX_NO_TIME_SLICE
#endif

#ifndef UX_DEVICE_APP_THREAD_START_OPTION
#define UX_DEVICE_APP_THREAD_START_OPTION TX_AUTO_START
#endif

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT MX_USBX_Device_Init(void);

#ifdef __cplusplus
}
#endif
