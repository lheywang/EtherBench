/**
 * @file 	configuration/storage.inc
 * @brief 	Sub configuration array to be seen as an MSC device (expose storage volumes)
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */
#pragma once

// ---------------------------------------------------------------------------
// MASS STORAGE CLASS (MSC) - Interface 4
// ---------------------------------------------------------------------------
#define DESC_MSC_LEN 23

#define DESC_MSC_BYTES \
    /* Interface 4 */ \
    0x09, 0x04, 0x04, 0x00, 0x02, 0x08, 0x06, 0x50, 0x00, \
    /* EP5 OUT */ \
    0x07, 0x05, 0x05, 0x02, 0x40, 0x00, 0x00, \
    /* EP5 IN */ \
    0x07, 0x05, 0x85, 0x02, 0x40, 0x00, 0x00
