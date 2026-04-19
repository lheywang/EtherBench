/**
 * @file    ll_vfs.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the low level VFS exposed callbacks. Theses are only trampolines
 *          that add an offset to the main flash.
 * @version 0.1
 * @date    2026-04-19
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                             INCLUDES
// ======================================================================
// Header
#include "ll_vfs.h"

// Local libraries
#include "GD5F1GO4UBY1G.h"
#include "commands.h"

// ThreadX
#include "tx_api.h"

// ======================================================================
//                            FUNCTIONS
// ======================================================================

// ------------------
// PAGE READ
// ------------------
UINT settings_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words) {
    return GD5F1GO4UBY1G_page_read(
        block + SETTINGS_PARTITION_OFFSET, page, destination, words);
}

UINT flash_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words) {
    return GD5F1GO4UBY1G_page_read(
        block + FLASH_PARTITION_OFFSET, page, destination, words);
}

UINT backtrace_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words) {
    return GD5F1GO4UBY1G_page_read(
        block + BACKTRACE_PARTITION_OFFSET, page, destination, words);
}

// ------------------
// PAGE WRITE
// ------------------
UINT settings_page_write(ULONG block, ULONG page, ULONG *source, ULONG words) {
    return GD5F1GO4UBY1G_page_write(
        block + SETTINGS_PARTITION_OFFSET, page, source, words);
}

UINT flash_page_write(ULONG block, ULONG page, ULONG *source, ULONG words) {
    return GD5F1GO4UBY1G_page_write(block + FLASH_PARTITION_OFFSET, page, source, words);
}

UINT backtrace_page_write(ULONG block, ULONG page, ULONG *source, ULONG words) {
    return GD5F1GO4UBY1G_page_write(
        block + BACKTRACE_PARTITION_OFFSET, page, source, words);
}

// ------------------
// BLOCK ERASE
// ------------------
UINT settings_block_erase(ULONG block, ULONG erase_count) {
    return GD5F1GO4UBY1G_block_erase(block + SETTINGS_PARTITION_OFFSET, erase_count);
}

UINT flash_block_erase(ULONG block, ULONG erase_count) {
    return GD5F1GO4UBY1G_block_erase(block + FLASH_PARTITION_OFFSET, erase_count);
}

UINT backtrace_block_erase(ULONG block, ULONG erase_count) {
    return GD5F1GO4UBY1G_block_erase(block + BACKTRACE_PARTITION_OFFSET, erase_count);
}

// ------------------
// BLOCK STATUS GET
// ------------------
UINT settings_block_status_get(ULONG block, UCHAR *bad_block_byte) {
    return GD5F1GO4UBY1G_block_status_get(
        block + SETTINGS_PARTITION_OFFSET, bad_block_byte);
}

UINT flash_block_status_get(ULONG block, UCHAR *bad_block_byte) {
    return GD5F1GO4UBY1G_block_status_get(block + FLASH_PARTITION_OFFSET, bad_block_byte);
}

UINT backtrace_block_status_get(ULONG block, UCHAR *bad_block_byte) {
    return GD5F1GO4UBY1G_block_status_get(
        block + BACKTRACE_PARTITION_OFFSET, bad_block_byte);
}

// ------------------
// BLOCK STATUS SET
// ------------------
UINT settings_block_status_set(ULONG block, UCHAR bad_block_byte) {
    return GD5F1GO4UBY1G_block_status_set(
        block + SETTINGS_PARTITION_OFFSET, bad_block_byte);
}

UINT flash_block_status_set(ULONG block, UCHAR bad_block_byte) {
    return GD5F1GO4UBY1G_block_status_set(block + FLASH_PARTITION_OFFSET, bad_block_byte);
}

UINT backtrace_block_status_set(ULONG block, UCHAR bad_block_byte) {
    return GD5F1GO4UBY1G_block_status_set(
        block + BACKTRACE_PARTITION_OFFSET, bad_block_byte);
}

// ------------------
// BLOCK ERASE VERIFY
// ------------------
UINT settings_block_erase_verify(ULONG block) {
    return GD5F1GO4UBY1G_block_erase_verify(block + SETTINGS_PARTITION_OFFSET);
}

UINT flash_block_erase_verify(ULONG block) {
    return GD5F1GO4UBY1G_block_erase_verify(block + FLASH_PARTITION_OFFSET);
}

UINT backtrace_block_erase_verify(ULONG block) {
    return GD5F1GO4UBY1G_block_erase_verify(block + BACKTRACE_PARTITION_OFFSET);
}

// ------------------
// PAGE ERASE VERIFY
// ------------------
UINT settings_page_erase_verify(ULONG block, ULONG page) {
    return GD5F1GO4UBY1G_page_erase_verify(block + SETTINGS_PARTITION_OFFSET, page);
}

UINT flash_page_erase_verify(ULONG block, ULONG page) {
    return GD5F1GO4UBY1G_page_erase_verify(block + FLASH_PARTITION_OFFSET, page);
}

UINT backtrace_page_erase_verify(ULONG block, ULONG page) {
    return GD5F1GO4UBY1G_page_erase_verify(block + BACKTRACE_PARTITION_OFFSET, page);
}
