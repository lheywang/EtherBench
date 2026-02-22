/**
 * @file 	ux_dummy.c
 * @brief 	Implement dummy USB callbacks, to be overridden by the user.
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "stm32h5xx_hal_def.h"

#include "ux_api.h"
#include "ux_device_stack.h"
#include "ux_device_class_cdc_acm.h"
#include "ux_device_class_storage.h"

// ======================================================================
//                              FUNCTIONS
// ======================================================================

__weak UINT msc_read(
		VOID *storage,
		ULONG lun,
		UCHAR *data_pointer,
		ULONG number_blocks,
		ULONG lba,
		ULONG *media_status
)
{
	return UX_SUCCESS;
}

__weak UINT msc_write(
		VOID *storage,
		ULONG lun,
		UCHAR *data_pointer,
		ULONG number_blocks,
		ULONG lba,
		ULONG *media_status
)
{
	return UX_SUCCESS;
}

__weak UINT msc_status(
		VOID *storage,
		ULONG lun,
		ULONG media_id,
		ULONG *media_status
)
{
	/* Not sure about the values here */
	*media_status = UX_SLAVE_CLASS_STORAGE_TEST_READY_OPERATION;

    if (lun == 1)
    	*media_status |= UX_SLAVE_CLASS_STORAGE_REQUEST_CODE_MEDIA_PROTECTED; // SD Card is Read-Only!

    return UX_SUCCESS;
}

