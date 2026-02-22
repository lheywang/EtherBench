/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_usbx_device.c
  * @author  MCD Application Team
  * @brief   USBX Device applicative file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_usbx_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "descriptors.h"

// USBX Core Headers
#include "ux_api.h"
#include "ux_device_stack.h"
#include "ux_device_class_cdc_acm.h"
#include "ux_device_class_storage.h"

// Overrides
#include "ux_dummy.h"

// OS
#include "tx_byte_pool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

static TX_THREAD ux_device_app_thread;

/* USER CODE BEGIN PV */
static uint8_t usbx_thread_stack[UX_DEVICE_APP_THREAD_STACK_SIZE];

UX_SLAVE_CLASS_CDC_ACM *serial_instance;
UX_SLAVE_CLASS_CDC_ACM *terminal_instance;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static VOID app_ux_device_thread_entry(ULONG thread_input);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Application USBX Device Initialization.
  * @param  memory_ptr: memory pointer
  * @retval status
  */

UINT MX_USBX_Device_Init(void)
{
   UINT ret = UX_SUCCESS;

  UCHAR *pointer;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)usbx_thread_stack;
  byte_pool->tx_byte_pool_id = TX_BYTE_POOL_ID;

  /* USER CODE BEGIN MX_USBX_Device_Init0 */

  /* USER CODE END MX_USBX_Device_Init0 */

  /* Allocate the stack for device application main thread */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer, UX_DEVICE_APP_THREAD_STACK_SIZE,
                       TX_NO_WAIT) != TX_SUCCESS)
  {
    /* USER CODE BEGIN MAIN_THREAD_ALLOCATE_STACK_ERROR */
    return TX_POOL_ERROR;
    /* USER CODE END MAIN_THREAD_ALLOCATE_STACK_ERROR */
  }

  /* Create the device application main thread */
  if (tx_thread_create(
		  &ux_device_app_thread,
		  UX_DEVICE_APP_THREAD_NAME,
		  app_ux_device_thread_entry,
          0, pointer,
		  UX_DEVICE_APP_THREAD_STACK_SIZE,
		  UX_DEVICE_APP_THREAD_PRIO,
          UX_DEVICE_APP_THREAD_PREEMPTION_THRESHOLD,
		  UX_DEVICE_APP_THREAD_TIME_SLICE,
          UX_DEVICE_APP_THREAD_START_OPTION
  ) != TX_SUCCESS)
  {
    /* USER CODE BEGIN MAIN_THREAD_CREATE_ERROR */
    return TX_THREAD_ERROR;
    /* USER CODE END MAIN_THREAD_CREATE_ERROR */
  }

  /* USER CODE BEGIN MX_USBX_Device_Init1 */

  /* USER CODE END MX_USBX_Device_Init1 */

  return ret;
}

/**
  * @brief  Function implementing app_ux_device_thread_entry.
  * @param  thread_input: User thread input parameter.
  * @retval none
  */
static VOID app_ux_device_thread_entry(ULONG thread_input)
{
  /* USER CODE BEGIN app_ux_device_thread_entry */
  TX_PARAMETER_NOT_USED(thread_input);
  UINT status;

  status = ux_device_stack_initialize(
          (UCHAR *)device_descriptor, 			DEVICE_DESCRIPTOR_LEN,
          (UCHAR *)configuration_descriptor, 	CONFIGURATION_DESCRIPTOR_LEN,
          (UCHAR *)string_framework, 			STRING_FRAMEWORK_LEN,
          (UCHAR *)language_id_framework, 		LANGUAGE_ID_FRAMEWORK_LEN,
          UX_NULL // No custom control endpoint handler needed
  );

  if (status != UX_SUCCESS) {
	  // Initialization failed! (Usually means your CONFIG_DESC_LENGTH math is wrong)
	  for (;;) {}
  }

  UX_SLAVE_CLASS_CDC_ACM_PARAMETER cdc_mux_param = {0};
  status = ux_device_stack_class_register(
	  (UCHAR *)"ux_device_class_cdc_acm",
	  ux_device_class_cdc_acm_entry,
	  1,  // Configuration 1
	  0,  // Interface 0
	  &cdc_mux_param
  );

  if (status != UX_SUCCESS) {
	  // Initialization failed! (Usually means your CONFIG_DESC_LENGTH math is wrong)
	  for (;;) {}
  }

  UX_SLAVE_CLASS_CDC_ACM_PARAMETER cdc_term_param = {0};
  status = ux_device_stack_class_register(
	  (UCHAR *)"ux_device_class_cdc_acm",
	  ux_device_class_cdc_acm_entry,
	  1,  // Configuration 1
	  2,  // Interface 2
	  &cdc_term_param
  );

  if (status != UX_SUCCESS) {
	  // Initialization failed! (Usually means your CONFIG_DESC_LENGTH math is wrong)
	  for (;;) {}
  }

  UX_SLAVE_CLASS_STORAGE_PARAMETER storage_param = {0};
  storage_param.ux_slave_class_storage_parameter_number_lun = 2;

  // LUN 0: QSPI (256MB)
  storage_param.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_last_lba = 524287;
  storage_param.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_block_length = 512;
  storage_param.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_type = 0;
  storage_param.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_removable_flag = 0x80;
  storage_param.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_read = msc_read;
  storage_param.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_write = msc_write;
  storage_param.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_status = msc_status;

  // LUN 1: SD Card (32GB)
  storage_param.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_last_lba = 62500000;
  storage_param.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_block_length = 512;
  storage_param.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_type = 0;
  storage_param.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_removable_flag = 0x80;
  storage_param.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_read = msc_read;
  storage_param.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_write = msc_write;
  storage_param.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_status = msc_status;

  status = ux_device_stack_class_register(
	  (UCHAR *)"ux_device_class_storage",
	  ux_device_class_storage_entry,
	  1,  // Configuration 1
	  4,  // Interface 4
	  &storage_param
  );

  if (status != UX_SUCCESS) {
	  // Initialization failed! (Usually means your CONFIG_DESC_LENGTH math is wrong)
	  for (;;) {}
  }

  // Register CDC 1
  status = ux_device_stack_class_register(
	  (UCHAR *)"ux_device_class_cdc_acm", // <-- Bulletproof string literal
	  ux_device_class_cdc_acm_entry,
	  1,  // Configuration 1
	  0,  // Interface 0
	  &cdc_mux_param
  );

  if (status != UX_SUCCESS) {
	  // Initialization failed! (Usually means your CONFIG_DESC_LENGTH math is wrong)
	  for (;;) {}
  }

  while (1)
  {
	  // The USB hardware interrupts handle the heavy lifting.
	  // This thread just sleeps, or we can use it later for background USB events.
	  tx_thread_sleep(100);
  }


  /* USER CODE END app_ux_device_thread_entry */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
