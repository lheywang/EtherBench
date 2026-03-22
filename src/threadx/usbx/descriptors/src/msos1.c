/**
 * @file msos1.c
 * @author lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date 2026-03-22
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "msos1.h"
#include "descriptor_config.h"

const ms_os_10_compat_id_t ms_os_10_descriptor = {
    .dwLength = sizeof(ms_os_10_compat_id_t),
    .bcdVersion = 0x0100,
    .wIndex = 0x0004,
    .bCount = 1,
    .Reserved = {0},
    .bFirstInterfaceNumber = DEBUGGER_INTERFACE_0,
    .bReserved1 = 0x01,
    .compatibleID = {'W', 'I', 'N', 'U', 'S', 'B', 0, 0},
    .subCompatibleID = {0},
    .Reserved2 = {0},
};