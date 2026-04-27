/**
 * @file    GD5F1GO4UBY1G.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   BSP for the GD5F1GO4UBY1G FLASH memory.
 * @version 0.1
 * @date    2026-04-16
 *
 * @copyright Copyright (c) 2026
 *
 * @details As this memory is NAND based, we cannot just map it into the memory
 * space as a NOR could be. That's still possible, but as we can't access a raw
 * address, the still need to pass trough an adaptation layer.
 *
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// ThreadX
#include "tx_api.h"

// HAL
#include "stm32h5xx_hal.h"
#include "stm32h5xx_hal_xspi.h"

// ======================================================================
//                           SHARED VARIABLES
// ======================================================================
// Main semaphore for the RTOS
extern TX_SEMAPHORE flash_wip;
extern TX_SEMAPHORE flash_dma_done;

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
 * @param destination Pointer to the location where the function shall place the
 * data.
 * @param words The number of words to be read.
 *
 * @return UINT
 * @retval LX_ERROR An error occured when writting to the device.
 * @retval LX_SUCESS The page was successfully read.
 */
UINT GD5F1GO4UBY1G_page_read(ULONG block, ULONG page, ULONG *destination, ULONG words);

/**
 * @brief Read more than one page on the GD5F device.
 *
 * @param block The target block
 * @param page The first page to be read
 * @param destination The target buffer
 * @param spare_buffer The ECC buffer. Unused.
 * @param pages The number of pages to be read
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_pages_read(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages);

/**
 * @brief Read the OOB bytes from a page on the FLASH. Usefull for the formatting and handling of the internal LevelX
 * IO.
 *
 * @param block The target block.
 * @param page The target page.
 * @param destination The destination in where we shall write the readout bytes.
 * @param size The number of bytes that must be read.
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_extra_bytes_get(ULONG block, ULONG page, UCHAR *destination, UINT size);

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

/**
 * @brief Perform write for more than a single page.
 *
 * @param block The target block
 * @param page The target, starting page address
 * @param main_buffer The main buffer to be used.
 * @param spare_buffer The ECC buffer. Unused.
 * @param pages The number of pages.
 * @return UINT
 */
UINT GD5F1GO4UBY1G_pages_write(ULONG block, ULONG page, UCHAR *main_buffer, UCHAR *spare_buffer, ULONG pages);

/**
 * @brief Perform a write for the OOB bytes on a target page.
 *
 * @param block The target block.
 * @param page The target page.
 * @param source The source bytes to be written.
 * @param size The size of the transfer.
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_extra_bytes_set(ULONG block, ULONG page, UCHAR *source, UINT size);

/**
 * @brief Perform a copy from a page to another one.
 *
 * @param src_block The source block.
 * @param src_page The source page
 * @param dest_block The destination block
 * @param dest_page The destination page
 * @param pages The number of pages to be copied
 * @param buffer A buffer to be used for the copying process. Unused (as the GD
 * Flash has hardware copy back !)
 * @return UINT
 */
UINT GD5F1GO4UBY1G_page_copy(ULONG src_block,
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

/**
 * @brief Set the protection byte into the FLASH.
 *
 * @param   status The protection byte. 0x00 for NONE.
 * @return  UINT
 */
UINT GD5F1GO4UBY1G_set_protected_blocks(UCHAR status);

/**
 * @brief Enable the QUAD-SPI communication mode.
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_enable_quad();

// ======================================================================
//                        FUNCTIONS (PRIVATE API)
// ======================================================================

/**
 * @brief Wait for the device to finish it's operation.
 *
 * @retval LX_ERROR Timeout was reached. Bus may be stalled, or a wrong command
 * was sent.
 * @retval LX_SUCESS The device finished it's pending operation.
 */
UINT GD5F1GO4UBY1G_wait_for_complete();

/**
 * @brief Enable the write operations on the flash.
 *
 * @warning This function is "private", as it better not be called outside of
 * it's context.
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_write_enable();

/**
 * @brief Disable the write operations on the flash.
 *
 * @warning This function is "private", as it better not be called outside of
 * it's context.
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_write_disable();

/**
 * @brief Reset the NAND flash to it's default config.
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_reset();

/**
 * @brief Perform a generic read of N bytes to the NAND.
 *
 * @param block The target blocK
 * @param page The target page
 * @param main_buffer The main buffer, size up to 2048 bytes.
 * @param main_size The main buffer size.
 * @param spare_buffer The spare buffer, for the OOB bytes.
 * @param spare_size The spare buffer size.
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_generic_read(ULONG block,
                                ULONG page,
                                UCHAR *main_buffer,
                                ULONG main_size,
                                UCHAR *spare_buffer,
                                ULONG spare_size);

/**
 * @brief Perform a generic write to the NAND device.
 *
 * @param block The target blocK
 * @param page The target page
 * @param main_buffer The main buffer, size up to 2048 bytes.
 * @param main_size The main buffer size.
 * @param spare_buffer The spare buffer, for the OOB bytes.
 * @param spare_size The spare buffer size.
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_generic_write(ULONG block,
                                 ULONG page,
                                 UCHAR *main_buffer,
                                 ULONG main_size,
                                 UCHAR *spare_buffer,
                                 ULONG spare_size);

// ======================================================================
//                           INTERRUPTS
// ======================================================================

/**
 * @brief All theses functions are overriding HAL functions. Ensure they're
 * correctly linked !
 */
void flash_command_complete();
void flash_tx_complete();
void flash_rx_complete();
void flash_polling_complete();

// ======================================================================
//                           RESCUE
// ======================================================================

/**
 * @brief Rescue the NAND from bad blocks. Will ERASE ALL BLOCKS. Nothing will
 * be checked. Used when debugging, do not use in prod at ALL !
 *
 * @return UINT
 */
UINT GD5F1GO4UBY1G_rescue();

/**
 * @brief Read a register from the nand, to debug some values.
 *
 * @param reg_addr
 */
UCHAR GD5F1GO4UBY1G_Read_Register(UCHAR reg_addr);