/**
 * @file 	configuration/cmsis.inc
 * @brief 	Sub configuration array, to be seen as CMSIS debugger
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */
#pragma once

// ---------------------------------------------------------------------------
// CUSTOM (CMSIS-DAP) - Interface 5
// ---------------------------------------------------------------------------
#define DESC_CMSIS_LEN 23

#define DESC_CMSIS_BYTES \
    /* Interface 5 (String idx 4) */ \
    0x09, 0x04, 0x05, 0x00, 0x02, 0xFF, 0x00, 0x00, 0x04, \
    /* EP6 OUT */ \
    0x07, 0x05, 0x06, 0x02, 0x40, 0x00, 0x00, \
    /* EP6 IN */ \
    0x07, 0x05, 0x86, 0x02, 0x40, 0x00, 0x00
