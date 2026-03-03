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
#include "descriptors2.h"

// USBX Core Headers
#include "ux_api.h"
#include "ux_device_class_cdc_acm.h"
#include "ux_device_class_storage.h"
#include "ux_device_stack.h"

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
extern PCD_HandleTypeDef hpcd_USB_DRD_FS;
extern void MX_USB_PCD_Init();
extern void HAL_PWREx_EnableVddUSB();
static TX_THREAD ux_device_app_thread;

/* USER CODE BEGIN PV */
static __attribute__((aligned(8))) uint8_t usbx_thread_stack[UX_DEVICE_APP_THREAD_STACK_SIZE];
static __attribute__((aligned(8))) uint8_t ux_memory[UX_SYSTEM_MEM_SIZE];
UX_SLAVE_CLASS_CDC_ACM *serial_instance;
UX_SLAVE_CLASS_CDC_ACM *terminal_instance;

UX_SLAVE_CLASS_CDC_ACM_PARAMETER cdc_mux_param = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static VOID app_ux_device_thread_entry(ULONG thread_input);
static UINT USBD_ChangeFunction(ULONG Device_State);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
 * @brief  Application USBX Device Initialization.
 * @param  memory_ptr: memory pointer
 * @retval status
 */

UINT MX_USBX_Device_Init(void) {

    /*
     * Initialize the USB system, and all the dedicated memory structs.
     */
    UINT status = ux_system_initialize(ux_memory, UX_SYSTEM_MEM_SIZE, UX_NULL, 0);
    if (status != UX_SUCCESS) {
        while (1)
            ;
    }

    /*
     * Launch the USB stack init
     */
    status = ux_device_stack_initialize((UCHAR *)&usb_device_desc, sizeof(usb_composite_configuration_tree_t),
                                        (UCHAR *)&usb_device_desc, sizeof(usb_composite_configuration_tree_t),
                                        (UCHAR *)&usb_device_string_framework, sizeof(usbx_string_framework_t),
                                        (UCHAR *)&usb_device_language_framework, sizeof(usbx_language_id_framework_t),
                                        USBD_ChangeFunction);

    if (status != UX_SUCCESS) {
        while (1) {
            tx_thread_sleep(100);
        }
    }

    status = ux_device_stack_class_register((UCHAR *)"cdc_terminal", ux_device_class_cdc_acm_entry,
                                            1, // Configuration 1
                                            0, // Interface 0
                                            &cdc_mux_param);

    if (status != UX_SUCCESS) {
        while (1) {
            tx_thread_sleep(100);
        }
    }

    /* Create the device application main thread */
    UINT ret =
        tx_thread_create(&ux_device_app_thread, UX_DEVICE_APP_THREAD_NAME, app_ux_device_thread_entry, 0,
                         usbx_thread_stack, UX_DEVICE_APP_THREAD_STACK_SIZE, 10, 10, TX_NO_TIME_SLICE, TX_AUTO_START);

    return ret;
}

/**
 * @brief  Function implementing app_ux_device_thread_entry.
 * @param  thread_input: User thread input parameter.
 * @retval none
 */
VOID app_ux_device_thread_entry(ULONG thread_input) {
    TX_PARAMETER_NOT_USED(thread_input);
    UINT status;

    HAL_PWREx_EnableVddUSB();

    tx_thread_sleep(2);

    MX_USB_PCD_Init();

    // Re-apply PMA here, after dcd init
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x00, PCD_SNG_BUF, 0x40);
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x80, PCD_SNG_BUF, 0x80);

    // --- Mémoire pour l'Interface CDC ---
    // EP1 IN (0x81) : Commandes / Interruption
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x81, PCD_SNG_BUF, 0xC0);

    // EP2 OUT (0x02) : Réception des données (RX)
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x02, PCD_SNG_BUF, 0x100);

    // EP2 IN (0x82) : Envoi des données (TX)
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x82, PCD_SNG_BUF, 0x140);

    /*
     * Turn ON the USB peripheral.
     */
    status = ux_dcd_stm32_initialize((ULONG)USB_DRD_BASE, (ULONG)&hpcd_USB_DRD_FS);
    if (status != UX_SUCCESS) {
        while (1)
            ;
    }

    tx_thread_sleep(10);

    /*
     * Enable the pull up (trigger enumeration) only at the end.
     */
    HAL_PCD_Start(&hpcd_USB_DRD_FS);

    while (1) {
        // The USB hardware interrupts handle the heavy lifting.
        // This thread just sleeps, or we can use it later for background USB
        // events.
        tx_thread_sleep(10);
    }

    /* USER CODE END app_ux_device_thread_entry */
    return;
}

static UINT USBD_ChangeFunction(ULONG Device_State) {
    UINT status = UX_SUCCESS;

    /* USER CODE BEGIN USBD_ChangeFunction0 */

    /* USER CODE END USBD_ChangeFunction0 */

    switch (Device_State) {
    case UX_DEVICE_ATTACHED:

        /* USER CODE BEGIN UX_DEVICE_ATTACHED */

        /* USER CODE END UX_DEVICE_ATTACHED */

        break;

    case UX_DEVICE_REMOVED:

        /* USER CODE BEGIN UX_DEVICE_REMOVED */

        /* USER CODE END UX_DEVICE_REMOVED */

        break;

    case UX_DCD_STM32_DEVICE_CONNECTED:

        /* USER CODE BEGIN UX_DCD_STM32_DEVICE_CONNECTED */

        /* USER CODE END UX_DCD_STM32_DEVICE_CONNECTED */

        break;

    case UX_DCD_STM32_DEVICE_DISCONNECTED:

        /* USER CODE BEGIN UX_DCD_STM32_DEVICE_DISCONNECTED */

        /* USER CODE END UX_DCD_STM32_DEVICE_DISCONNECTED */

        break;

    case UX_DCD_STM32_DEVICE_SUSPENDED:

        /* USER CODE BEGIN UX_DCD_STM32_DEVICE_SUSPENDED */

        /* USER CODE END UX_DCD_STM32_DEVICE_SUSPENDED */

        break;

    case UX_DCD_STM32_DEVICE_RESUMED:

        /* USER CODE BEGIN UX_DCD_STM32_DEVICE_RESUMED */

        /* USER CODE END UX_DCD_STM32_DEVICE_RESUMED */

        break;

    case UX_DCD_STM32_SOF_RECEIVED:

        /* USER CODE BEGIN UX_DCD_STM32_SOF_RECEIVED */

        /* USER CODE END UX_DCD_STM32_SOF_RECEIVED */

        break;

    default:

        /* USER CODE BEGIN DEFAULT */

        /* USER CODE END DEFAULT */

        break;
    }

    /* USER CODE BEGIN USBD_ChangeFunction1 */

    /* USER CODE END USBD_ChangeFunction1 */

    return status;
}
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
