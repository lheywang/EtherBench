/**
 * @file msos1.h
 * @author lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date 2026-03-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once
#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint32_t dwLength;
    uint16_t bcdVersion;
    uint16_t wIndex;
    uint8_t bCount;
    uint8_t Reserved[7];
    // Function 0 (Interface 0 - Debugger)
    uint8_t bFirstInterfaceNumber;
    uint8_t bReserved1;
    uint8_t compatibleID[8]; // "WINUSB\0\0"
    uint8_t subCompatibleID[8];
    uint8_t Reserved2[6];
} ms_os_10_compat_id_t;

extern const ms_os_10_compat_id_t ms_os_10_descriptor;