/**
 * @file 	ux_dummy.h
 * @brief 	Define dummy USB callbacks, to be overridden by the user.
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "ux_api.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/**
 * @brief 	Implement a do_nothing msc_read function. Need to be implemented by the user
 * 			in the final application.
 */
UINT msc_read(
		VOID *storage,
		ULONG lun,
		UCHAR *data_pointer,
		ULONG number_blocks,
		ULONG lba,
		ULONG *media_status
);

/**
 * @brief 	Implement a do_nothing msc_write function. Need to be implemented by the user
 * 			in the final application.
 */
UINT msc_write(
		VOID *storage,
		ULONG lun,
		UCHAR *data_pointer,
		ULONG number_blocks,
		ULONG lba,
		ULONG *media_status
);

/**
 * @brief 	Implement a do_nothing msc_status function. Need to be implemented by the user
 * 			in the final application.
 */
UINT msc_status(
		VOID *storage,
		ULONG lun,
		ULONG media_id,
		ULONG *media_status
);

