/**
 * @file    app_usbx_device.c
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Handle the USBX core initialization and config.
 * @version 0.1
 * @date    2026-03-04
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "descriptors2.h"

// Local libraries
#include "app_usbx_device.h"
#include "app_usbx_status.h"

#define LOG_MODULE "USBX_APP"
#include "logger.h"

// USBX Core Headers
#include "ux_api.h"
#include "ux_device_class_cdc_acm.h"
#include "ux_device_class_dpump.h"
#include "ux_device_class_storage.h"
#include "ux_device_stack.h"

// Overrides
#include "ux_dummy.h"

// OS
#include "tx_byte_pool.h"
#include "tx_handler.h"

// ======================================================================
//                              EXTERNS
// ======================================================================
// Variables
extern PCD_HandleTypeDef hpcd_USB_DRD_FS;
extern TX_EVENT_FLAGS_GROUP usbx_app_flags;

// Functions (as we cannot link against the HAL, otherwise --> Circular
// dependencies)
extern void MX_USB_PCD_Init();
extern void HAL_PWREx_EnableVddUSB();
extern void Error_Handler();

// ======================================================================
//                              VARIABLES
// ======================================================================
// Thread handle
static TX_THREAD ux_device_app_thread;

// memory buffers
static __aligned(8) uint8_t usbx_thread_stack[UX_DEVICE_APP_THREAD_STACK_SIZE];
static __aligned(8) uint8_t ux_memory[UX_SYSTEM_MEM_SIZE];

// USBX slaves
UX_SLAVE_CLASS_CDC_ACM_PARAMETER cdc_terminal = {0};
UX_SLAVE_CLASS_CDC_ACM_PARAMETER cdc_usb_usart = {0};
UX_SLAVE_CLASS_STORAGE_PARAMETER msc_files = {0};
UX_SLAVE_CLASS_DPUMP_PARAMETER cmsis_dap = {0};

// ======================================================================
//                              FUNCTIONS
// ======================================================================
// Static
static VOID app_ux_device_thread_entry(ULONG thread_input);

// Impl
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
    if (status != UX_SUCCESS)
        Error_Handler();

    /*
     * Launch the USB stack init with the descriptors
     */
    status = ux_device_stack_initialize(
        (UCHAR *)&usb_device_desc,
        sizeof(usb_composite_configuration_tree_t),
        (UCHAR *)&usb_device_desc,
        sizeof(usb_composite_configuration_tree_t),
        (UCHAR *)&usb_device_string_framework,
        sizeof(usbx_string_framework_t),
        (UCHAR *)&usb_device_language_framework,
        sizeof(usbx_language_id_framework_t),
        USBD_ChangeFunction);

    if (status != UX_SUCCESS)
        Error_Handler();
    LOG("Initialized the USBX stack.");

    /*
     * Add the USB classes
     */
    // CDC TERMINAL
    cdc_terminal.ux_slave_class_cdc_acm_instance_activate = USBX_TerminalEnable;
    cdc_terminal.ux_slave_class_cdc_acm_instance_deactivate = USBX_TerminalDisable;
    cdc_terminal.ux_slave_class_cdc_acm_parameter_change = USBX_TerminalChange;

    status = ux_device_stack_class_register(
        (UCHAR *)"cdc_terminal", ux_device_class_cdc_acm_entry, 1, 0, &cdc_terminal);

    if (status != UX_SUCCESS)
        Error_Handler();
    LOG("Registered CDC TERMINAL.");

    // USB USART BRIDGE
    cdc_usb_usart.ux_slave_class_cdc_acm_instance_activate = USBX_USARTBridgeEnable;
    cdc_usb_usart.ux_slave_class_cdc_acm_instance_deactivate = USBX_USARTBridgeDisable;
    cdc_usb_usart.ux_slave_class_cdc_acm_parameter_change = USBX_USARTBridgeChange;

    status = ux_device_stack_class_register(
        (UCHAR *)"cdc_vcom", ux_device_class_cdc_acm_entry, 1, 2, &cdc_usb_usart);

    if (status != UX_SUCCESS)
        Error_Handler();
    LOG("Registered CDC USB UART BRIDGE.");

    // MSC
    msc_files.ux_slave_class_storage_instance_activate = USBX_MSCEnable;
    msc_files.ux_slave_class_storage_instance_deactivate = USBX_MSCDisable;

    // Set the LUN count
    msc_files.ux_slave_class_storage_parameter_number_lun = 2;

    // --- LUN 0 : Embeddded Flash (128 MB)
    msc_files.ux_slave_class_storage_parameter_lun[0]
        .ux_slave_class_storage_media_last_lba = 262143;
    msc_files.ux_slave_class_storage_parameter_lun[0]
        .ux_slave_class_storage_media_block_length = 512;
    msc_files.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_type =
        0;
    msc_files.ux_slave_class_storage_parameter_lun[0]
        .ux_slave_class_storage_media_removable_flag =
        0x80;
    msc_files.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_read =
        msc_read;
    msc_files.ux_slave_class_storage_parameter_lun[0].ux_slave_class_storage_media_write =
        msc_write;
    msc_files.ux_slave_class_storage_parameter_lun[0]
        .ux_slave_class_storage_media_status = msc_status;

    // --- LUN 1 : SD Card (32 GB theoritical size, to be changed)
    msc_files.ux_slave_class_storage_parameter_lun[1]
        .ux_slave_class_storage_media_last_lba = 67108863;
    msc_files.ux_slave_class_storage_parameter_lun[1]
        .ux_slave_class_storage_media_block_length = 512;
    msc_files.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_type =
        0;
    msc_files.ux_slave_class_storage_parameter_lun[1]
        .ux_slave_class_storage_media_removable_flag = 0x80;
    msc_files.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_read =
        msc_read;
    msc_files.ux_slave_class_storage_parameter_lun[1].ux_slave_class_storage_media_write =
        msc_write;
    msc_files.ux_slave_class_storage_parameter_lun[1]
        .ux_slave_class_storage_media_status = msc_status;

    status = ux_device_stack_class_register(
        (UCHAR *)"msc_storage", ux_device_class_storage_entry, 1, 4, (VOID *)&msc_files);

    if (status != UX_SUCCESS)
        Error_Handler();
    LOG("Registered MSC flash + SD.");

    // CMSIS-DEBUGGER
    cmsis_dap.ux_slave_class_dpump_instance_activate = USBX_CMSISEnable;
    cmsis_dap.ux_slave_class_dpump_instance_deactivate = USBX_CMSISDisable;

    status = ux_device_stack_class_register(
        (UCHAR *)"cmsis_dap", ux_device_class_dpump_entry, 1, 5, (VOID *)&cmsis_dap);

    if (status != UX_SUCCESS)
        Error_Handler();
    LOG("Registered CMSIS Debugger.");

    /*
     * Create the main application thread
     */
    status = tx_thread_create(
        &ux_device_app_thread,
        UX_DEVICE_APP_THREAD_NAME,
        app_ux_device_thread_entry,
        0,
        usbx_thread_stack,
        UX_DEVICE_APP_THREAD_STACK_SIZE,
        10,
        10,
        TX_NO_TIME_SLICE,
        TX_AUTO_START);

    if (status != UX_SUCCESS)
        Error_Handler();
    LOG("Launched USBX task.");

    /*
     * Create the communications flags
     */
    tx_event_flags_create(&usbx_app_flags, "usb_app_flags");

    return UX_SUCCESS;
}

/**
 * @brief  Function implementing app_ux_device_thread_entry.
 * @param  thread_input: User thread input parameter.
 * @retval none
 */
VOID app_ux_device_thread_entry(ULONG thread_input) {
    TX_PARAMETER_NOT_USED(thread_input);
    UINT status;

    /*
     * Enable peripheral power, and let it stabiliize.
     */
    HAL_PWREx_EnableVddUSB();
    tx_thread_sleep(2);
    LOG("Enabled USB peripheral power supply.");

    /*
     * Initialize the peripheral config and declare the endpoints.
     */
    MX_USB_PCD_Init();

    // Config IO
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x00, PCD_SNG_BUF, 0x040);
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x80, PCD_SNG_BUF, 0x080);

    // CDC TERMINAL
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x81, PCD_SNG_BUF, 0x0C0);
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x02, PCD_SNG_BUF, 0x100);
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x82, PCD_SNG_BUF, 0x140);

    // CDC VCOM
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x83, PCD_SNG_BUF, 0x180);
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x04, PCD_SNG_BUF, 0x1C0);
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x84, PCD_SNG_BUF, 0x200);

    // MSC
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x85, PCD_SNG_BUF, 0x240);
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x05, PCD_SNG_BUF, 0x280);

    // CMSIS-DAP
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x86, PCD_SNG_BUF, 0x2C0);
    HAL_PCDEx_PMAConfig(&hpcd_USB_DRD_FS, 0x06, PCD_SNG_BUF, 0x300);

    LOG("Configured USB peripheral and endpoints.");

    /*
     * Turn ON the USB peripheral.
     */
    status = ux_dcd_stm32_initialize((ULONG)USB_DRD_BASE, (ULONG)&hpcd_USB_DRD_FS);
    if (status != UX_SUCCESS) {
        Tx_Error_Handler(USB_HW_CONFIG_FAILED);
    }
    LOG("Initialized USBX STM32 BSP.");

    /*
     * Let the peripheral start
     */
    tx_thread_sleep(10);

    /*
     * Enable the pull up (trigger enumeration) only at the end.
     */
    if (HAL_PCD_Start(&hpcd_USB_DRD_FS) != HAL_OK)
        Tx_Error_Handler(USB_HW_CANNOT_START);
    LOG("Started USB enumeration process.");

    /*
     * Finally, make the thread sleep for always. We use large delays because
     * that will just let the scheduler be more flexible.
     */
    while (1) {
        tx_thread_sleep(10000);
    }

    return;
}

