/**
 * @file    status.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the status features of the GD5F1GO4UBY1G flash.
 * @version 0.1
 * @date    2026-04-16
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "commands.h"

// LevelX
#include "lx_api.h"

// ThreadX
#include "tx_api.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

UINT GD5F1GO4UBY1G_block_status_get(ULONG block, UCHAR *bad_block_byte) {
    (void)(block);
    (void)(bad_block_byte);
    return LX_ERROR;
}

UINT GD5F1GO4UBY1G_block_status_set(ULONG block, UCHAR bad_block_byte) {
    (void)(block);
    (void)(bad_block_byte);
    return LX_ERROR;
}
