/**
 * @file    usb.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   USB bus init code
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

extern PCD_HandleTypeDef hpcd_USB_DRD_FS;

// ======================================================================
//                              FUNCTIONS
// ======================================================================

void MX_USB_PCD_Init(void);

#ifdef __cplusplus
}
#endif
