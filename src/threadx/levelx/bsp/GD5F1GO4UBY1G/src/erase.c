/**
 * @file    erase.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the erase features of the GD5F1GO4UBY1G flash.
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

UINT GD5F1GO4UBY1G_block_erase(ULONG block, ULONG erase_count) {
    (void)(block);
    (void)(erase_count);
    return LX_ERROR;
}
