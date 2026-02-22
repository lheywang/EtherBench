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
  /* USER CODE END app_ux_device_thread_entry */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
