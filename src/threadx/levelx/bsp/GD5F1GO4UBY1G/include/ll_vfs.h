/**
 * @file    ll_vfs.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   low level virtual file system interface for the NAND memory.
 * @version 0.1
 * @date    2026-04-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                             INCLUDES
// ======================================================================
// Local libraries
#include "GD5F1GO4UBY1G.h"
#include "commands.h"

// ThreadX
#include "tx_api.h"

// ======================================================================
//                             DEFINES
// ======================================================================
// Partitions sizes
#define SETTINGS_PARTITION_SIZE  10
#define BACKTRACE_PARTITION_SIZE 10
#define FLASH_PARTITION_SIZE     (GD25_BLOCK_COUNT_NORMAL - BACKTRACE_PARTITION_SIZE)

// Partitions offsets
#define SETTINGS_PARTITION_OFFSET  0
#define FLASH_PARTITION_OFFSET     10
#define BACKTRACE_PARTITION_OFFSET (GD25_BLOCK_COUNT_NORMAL - BACKTRACE_PARTITION_SIZE)

// ======================================================================
//                            FUNCTIONS
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
UINT settings_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words);
UINT flash_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words);
UINT backtrace_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words);

UINT settings_pages_read(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages);
UINT flash_pages_read(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages);
UINT backtrace_pages_read(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages);

UINT settings_extra_bytes_get(ULONG block, ULONG page, UCHAR *destination, UINT size);
UINT flash_extra_bytes_get(ULONG block, ULONG page, UCHAR *destination, UINT size);
UINT backtrace_extra_bytes_get(ULONG block, ULONG page, UCHAR *destination, UINT size);

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
UINT settings_page_write(ULONG block, ULONG page, ULONG *source, ULONG words);
UINT flash_page_write(ULONG block, ULONG page, ULONG *source, ULONG words);
UINT backtrace_page_write(ULONG block, ULONG page, ULONG *source, ULONG words);

UINT settings_pages_write(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages);
UINT flash_pages_write(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages);
UINT backtrace_pages_write(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages);

UINT settings_extra_bytes_set(ULONG block, ULONG page, UCHAR *source, UINT size);
UINT flash_extra_bytes_set(ULONG block, ULONG page, UCHAR *source, UINT size);
UINT backtrace_extra_bytes_set(ULONG block, ULONG page, UCHAR *source, UINT size);

/**
 * @brief Perform a copy from a page to another one.
 *
 * @param src_block The source block.
 * @param src_page The source page
 * @param dest_block The destination block
 * @param dest_page The destination page
 * @param pages The number of pages to be copied
 * @return UINT
 */
UINT settings_page_copy(ULONG src_block, ULONG src_page, ULONG dest_block, ULONG dest_page, ULONG pages, UCHAR *buffer);
UINT flash_page_copy(ULONG src_block, ULONG src_page, ULONG dest_block, ULONG dest_page, ULONG pages, UCHAR *buffer);
UINT backtrace_page_copy(ULONG src_block,
                         ULONG src_page,
                         ULONG dest_block,
                         ULONG dest_page,
                         ULONG pages,
                         UCHAR *buffer);

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
UINT settings_block_erase(ULONG block, ULONG erase_count);
UINT flash_block_erase(ULONG block, ULONG erase_count);
UINT backtrace_block_erase(ULONG block, ULONG erase_count);

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
UINT settings_block_status_get(ULONG block, UCHAR *bad_block_byte);
UINT flash_block_status_get(ULONG block, UCHAR *bad_block_byte);
UINT backtrace_block_status_get(ULONG block, UCHAR *bad_block_byte);

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
UINT settings_block_status_set(ULONG block, UCHAR bad_block_byte);
UINT flash_block_status_set(ULONG block, UCHAR bad_block_byte);
UINT backtrace_block_status_set(ULONG block, UCHAR bad_block_byte);

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
UINT settings_block_erase_verify(ULONG block);
UINT flash_block_erase_verify(ULONG block);
UINT backtrace_block_erase_verify(ULONG block);

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
UINT settings_page_erase_verify(ULONG block, ULONG page);
UINT flash_page_erase_verify(ULONG block, ULONG page);
UINT backtrace_page_erase_verify(ULONG block, ULONG page);
