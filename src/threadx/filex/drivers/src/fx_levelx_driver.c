/**
 * @file    fx_levelx_driver.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Logic glue from LevelX to FileX
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
#include "fx_levelx_driver.h"

// FileX
#include "fx_api.h"

// LevelX
#include "lx_api.h"

// ======================================================================
//                             FUNCTIONS
// ======================================================================
/**
 * @brief Implement the basic LevelX virtual driver.
 *
 * @param   media_ptr The accessed ressource
 * @return  VOID
 */
VOID fx_levelx_nand_driver(FX_MEDIA *media_ptr) {

    LX_NAND_FLASH *nand_flash;
    UINT status = LX_SUCCESS;
    ULONG sector;
    ULONG count;
    ULONG *buffer;

    /*
     * Fetch the NAND struct
     */
    nand_flash = (LX_NAND_FLASH *)media_ptr->fx_media_driver_info;
    if (nand_flash == NULL) {
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
        return;
    }

    /*
     * Route the correct request to the correct interface
     */
    switch (media_ptr->fx_media_driver_request) {

    /*
     * Init is already handled before FileX did start. Nothing to do.
     */
    case FX_DRIVER_INIT:
    case FX_DRIVER_UNINIT:
        media_ptr->fx_media_driver_status = FX_SUCCESS;
        break;

    /*
     * Read operations
     */
    case FX_DRIVER_READ:
    case FX_DRIVER_BOOT_READ:
        sector = media_ptr->fx_media_driver_logical_sector;
        count = media_ptr->fx_media_driver_sectors;
        buffer = (ULONG *)media_ptr->fx_media_driver_buffer;

        while (count--) {
            status = lx_nand_flash_sector_read(nand_flash, sector, buffer);
            if (status != LX_SUCCESS) {
                break;
            }
            sector++;
            buffer += (media_ptr->fx_media_bytes_per_sector / sizeof(ULONG));
        }
        media_ptr->fx_media_driver_status =
            (status == LX_SUCCESS) ? FX_SUCCESS : FX_IO_ERROR;
        break;

    /*
     * Writes
     */
    case FX_DRIVER_WRITE:
    case FX_DRIVER_BOOT_WRITE:
        sector = media_ptr->fx_media_driver_logical_sector;
        count = media_ptr->fx_media_driver_sectors;
        buffer = (ULONG *)media_ptr->fx_media_driver_buffer;

        while (count--) {
            status = lx_nand_flash_sector_write(nand_flash, sector, buffer);
            if (status != LX_SUCCESS) {
                break;
            }
            sector++;
            buffer += (media_ptr->fx_media_bytes_per_sector / sizeof(ULONG));
        }
        media_ptr->fx_media_driver_status =
            (status == LX_SUCCESS) ? FX_SUCCESS : FX_IO_ERROR;
        break;

    /*
     * Our driver does not support theses operations. So, just return success.
     */
    case FX_DRIVER_FLUSH:
    case FX_DRIVER_ABORT:
        media_ptr->fx_media_driver_status = FX_SUCCESS;
        break;

    /*
     * Unknown command. Return error.
     */
    default:
        media_ptr->fx_media_driver_status = FX_IO_ERROR;
        break;
    }
}