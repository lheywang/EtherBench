/**
 * @file    GD5F1GO4UBY1G.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   BSP for the GD5F1GO4UBY1G FLASH memory.
 * @version 0.1
 * @date    2026-04-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// ThreadX
#include "tx_api.h"

// ======================================================================
//                        FUNCTIONS (PUBLIC API)
// ======================================================================

/*
 * Page IO
 */
/**
 * @brief Read a page from the GD5F1GO4UBY1G device.
 *
 * @param block The target block to be read.
 * @param page The target page to be read.
 * @param destination Pointer to the location where the function shall place the data.
 * @param words The number of words to be read.
 *
 * @return UINT
 * @retval LX_ERROR An error occured when writting to the device.
 * @retval LX_SUCESS The page was successfully read.
 */
UINT GD5F1GO4UBY1G_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words);

/**
 * @brief Write a page on the GD5F1GO4UBY1G device.
 *
 * @param block The target block to be read.
 * @param page The target page to be read.
 * @param source Pointer to the source of the data to be written.
 * @param words The number of words to be wrote.
 *
 * @return UINT
 * @retval LX_ERROR An error occured when reading from the device.
 * @retval LX_SUCESS The page was successfully wrote.
 */
UINT GD5F1GO4UBY1G_page_write(ULONG block, ULONG page, ULONG *source, ULONG words);

/*
 * Erase
 */

/**
 * @brief Start a block erase.
 *
 * @param block The target block to be reased.
 * @param erase_count The size to be erased (blocks counts).
 *
 * @return UINT
 * @retval LX_ERROR An error occured when erasing from the device.
 * @retval LX_SUCESS The page was successfully erased.
 */
UINT GD5F1GO4UBY1G_block_erase(ULONG block, ULONG erase_count);

/*
 * Bad blocks handling
 */
/**
 * @brief Get the block status (bad block ? )
 *
 * @param block The target block.
 * @param bad_block_byte Return the bad block marker value.
 *
 * @return UINT
 * @retval LX_ERROR An error occured when reading from the device.
 * @retval LX_SUCESS The marker was successfully read.
 */
UINT GD5F1GO4UBY1G_block_status_get(ULONG block, UCHAR *bad_block_byte);

/**
 * @brief Set the block status (bad block)
 *
 * @param block The target block.
 * @param bad_block_byte The value to be set.
 *
 * @return UINT
 * @retval LX_ERROR An error occured when writting from the device.
 * @retval LX_SUCESS The marker was successfully wrote.
 */
UINT GD5F1GO4UBY1G_block_status_set(ULONG block, UCHAR bad_block_byte);

/*
 * Write verifications
 */

/**
 * @brief Check for a correct block erasing.
 *
 * @param block The target block
 *
 * @return UINT
 * @retval LX_ERROR The block was not erased.
 * @retval LX_SUCESS The block was erased.
 */
UINT GD5F1GO4UBY1G_block_erase_verify(ULONG block);

/**
 * @brief Check for a page erasing.
 *
 * @param block The target block
 * @param page
 *
 * @return UINT
 * @retval LX_ERROR The page was not erased.
 * @retval LX_SUCESS The page was erased.
 */
UINT GD5F1GO4UBY1G_page_erase_verify(ULONG block, ULONG page);

// ======================================================================
//                        FUNCTIONS (PRIVATE API)
// ======================================================================

/**
 * @brief Wait for the device to finish it's operation.
 *
 * @retval LX_ERROR Timeout was reached. Bus may be stalled, or a wrong command was sent.
 * @retval LX_SUCESS The device finished it's pending operation.
 */
UINT GD5F1GO4UBY1G_wait_for_complete();