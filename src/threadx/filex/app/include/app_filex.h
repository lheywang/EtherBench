/**
 * @file    app_filex.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-04-15
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
// ThreadX
#include "tx_handler.h"

// FileX
#include "fx_api.h"
#include "fx_stm32_custom_driver.h"
#include "fx_stm32_sd_driver.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================
UINT MX_FileX_Init();

// ======================================================================
//                              DEFINES
// ======================================================================

#define FX_APP_THREAD_STACK_SIZE 3072
#define FX_APP_THREAD_PRIO 10

#ifndef FX_APP_THREAD_NAME
#define FX_APP_THREAD_NAME "FileX app thread"
#endif

/* Main thread time slice */
#ifndef FX_APP_THREAD_TIME_SLICE
#define FX_APP_THREAD_TIME_SLICE TX_NO_TIME_SLICE
#endif

/* Main thread auto start */
#ifndef FX_APP_THREAD_AUTO_START
#define FX_APP_THREAD_AUTO_START TX_AUTO_START
#endif

/* Main thread preemption threshold */
#ifndef FX_APP_PREEMPTION_THRESHOLD
#define FX_APP_PREEMPTION_THRESHOLD FX_APP_THREAD_PRIO
#endif

/* fx sd volume name */
#ifndef FX_SD_VOLUME_NAME
#define FX_SD_VOLUME_NAME "STM32_SDIO_DISK"
#endif

/* fx sd number of FATs */
#ifndef FX_SD_NUMBER_OF_FATS
#define FX_SD_NUMBER_OF_FATS 1
#endif

/* fx sd Hidden sectors */
#ifndef FX_SD_HIDDEN_SECTORS
#define FX_SD_HIDDEN_SECTORS 0
#endif

#ifdef __cplusplus
}
#endif