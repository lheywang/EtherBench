/**
 * @file 	descriptors2.c
 * @brief 	Second version of the USB descriptors.
 *
 * @details This second version (and perhaps only one, if I deleted the previous
 * one) is based on compile time resolved symbols rather than live execution
 * ones. This is cleaner, and, a bit faster.
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	03/03/2026
 * @version 0.1
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "descriptors2.h"

// STD
#include <stdint.h>

/*
 * Here we just need to instantiate a global struct, defined as const.
 * And the magic will happen : No CPU load, just pure flash read.
 */
const usb_composite_configuration_tree_t usb_device_desc = {

    .device =
        {
            .bLength = sizeof(usb_device_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_DEVICE,
            .bcdUSB = USB_BCDC_USB2_0,
            .bDeviceClass = USB_CLASS_MISC,
            .bDeviceSubClass = USB_SUBCLASS_MISC,
            .bDeviceProtocol = USB_PROTOCOL_MISC_IAD,
            .bMaxPacketSize0 = 64,
            .idVendor = ST_VENDORID,
            .idProduct = ST_PRODUCTID,
            .bcdDevice = DEVICE_ID,
            .iManufacturer = 1,
            .iProduct = 2,
            .iSerialNumber = 3,
            .bNumConfigurations = 1,
        },

    .config =
        {
            .bLength = sizeof(usb_config_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_CONFIGURATION,
            .wTotalLength =
                (sizeof(usb_composite_configuration_tree_t) -
                 sizeof(usb_device_descriptor_t)),
            .bNumInterfaces = 6,
            .bConfigurationValue = 1,
            .iConfiguration = 0,
            .bmAttributes = USB_ATTR_BUS_POWERED,
            .bMaxPower = USB_PWR_100MA,
        },

    // ==========================================
    // COM PORT (TERMINAL). INTERFACES 0 and 1
    // ==========================================
    // IAD 1
    .iad_cdc_1 =
        {
            .bLength = sizeof(usb_iad_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_IAD,
            .bFirstInterface = 0,
            .bInterfaceCount = 2,
            .bFunctionClass = USB_CLASS_CDC,
            .bFunctionSubClass = USB_SUBCLASS_CDC_ACM,
            .bFunctionProtocol = USB_PROTOCOL_NONE,
            .iFunction = 4,
        },

    // INTERFACE 0
    .itf_comm_1 =
        {
            .bLength = sizeof(usb_interface_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_INTERFACE,
            .bInterfaceNumber = 0,
            .bAlternateSetting = 0x00,
            .bNumEndpoints = 1,
            .bInterfaceClass = USB_CLASS_CDC,
            .bInterfaceSubClass = USB_SUBCLASS_CDC_ACM,
            .bInterfaceProtocol = USB_PROTOCOL_NONE,
            .iInterface = 0x00,
        },
    .cdc_hdr_1 =
        {
            .bLength = sizeof(cdc_header_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_CDC_INTERFACE,
            .bDescriptorSubtype = USB_DESC_SUBTYPE_CDC_HEADER,
            .bcdCDC = USB_CDC_bCDC,
        },
    .cdc_mgmt_1 =
        {
            .bLength = sizeof(cdc_call_mgmt_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_CDC_INTERFACE,
            .bDescriptorSubtype = USB_DESC_SUBTYPE_CDC_MGNT,
            .bmCapabilities = 0x00,
            .bDataInterface = 0x01,
        },
    .cdc_acm_1 =
        {
            .bLength = sizeof(cdc_acm_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_CDC_INTERFACE,
            .bDescriptorSubtype = USB_DESC_SUBTYPE_CDC_ACM,
            .bmCapabilities = 0x02,
        },
    .cdc_union_1 =
        {
            .bLength = sizeof(cdc_union_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_CDC_INTERFACE,
            .bDescriptorSubtype = USB_DESC_SUBTYPE_CDC_UNION,
            .bMasterInterface = 0,
            .bSlaveInterface0 = 1,
        },
    .ep_comm_int_1 =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_IN | 1),
            .bEndpointType = USB_ENDP_INT,
            .wMaxPacketSize = 8,
            .bInterval = USB_INTERVAL_FS_LS_INT(32),
        },

    // INTERFACE 1
    .itf_data_1 =
        {
            .bLength = sizeof(usb_interface_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_INTERFACE,
            .bInterfaceNumber = 1,
            .bAlternateSetting = 0x00,
            .bNumEndpoints = 2,
            .bInterfaceClass = USB_CLASS_CDC_DATA,
            .bInterfaceSubClass = USB_SUBCLASS_NONE,
            .bInterfaceProtocol = USB_PROTOCOL_NONE,
            .iInterface = 0,
        },
    .ep_data_out_1 =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_OUT | 2),
            .bEndpointType = USB_ENDP_BULK,
            .wMaxPacketSize = 64,
            .bInterval = 0x00,
        },
    .ep_data_in_1 =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_IN | 2),
            .bEndpointType = USB_ENDP_BULK,
            .wMaxPacketSize = 64,
            .bInterval = 0x00,
        },

    // ==========================================
    // COM PORT (USB-USART). INTERFACES 2 and 3
    // ==========================================
    // IAD 2
    .iad_cdc_2 =
        {
            .bLength = sizeof(usb_iad_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_IAD,
            .bFirstInterface = 2,
            .bInterfaceCount = 2,
            .bFunctionClass = USB_CLASS_CDC,
            .bFunctionSubClass = USB_SUBCLASS_CDC_ACM,
            .bFunctionProtocol = USB_PROTOCOL_NONE,
            .iFunction = 5,
        },

    // INTERFACE 2
    .itf_comm_2 =
        {
            .bLength = sizeof(usb_interface_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_INTERFACE,
            .bInterfaceNumber = 2,
            .bAlternateSetting = 0x00,
            .bNumEndpoints = 1,
            .bInterfaceClass = USB_CLASS_CDC,
            .bInterfaceSubClass = USB_SUBCLASS_CDC_ACM,
            .bInterfaceProtocol = USB_PROTOCOL_NONE,
            .iInterface = 0x00,
        },
    .cdc_hdr_2 =
        {
            .bLength = sizeof(cdc_header_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_CDC_INTERFACE,
            .bDescriptorSubtype = USB_DESC_SUBTYPE_CDC_HEADER,
            .bcdCDC = USB_CDC_bCDC,
        },
    .cdc_mgmt_2 =
        {
            .bLength = sizeof(cdc_call_mgmt_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_CDC_INTERFACE,
            .bDescriptorSubtype = USB_DESC_SUBTYPE_CDC_MGNT,
            .bmCapabilities = 0x00,
            .bDataInterface = 0x01,
        },
    .cdc_acm_2 =
        {
            .bLength = sizeof(cdc_acm_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_CDC_INTERFACE,
            .bDescriptorSubtype = USB_DESC_SUBTYPE_CDC_ACM,
            .bmCapabilities = 0x02,
        },
    .cdc_union_2 =
        {
            .bLength = sizeof(cdc_union_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_CDC_INTERFACE,
            .bDescriptorSubtype = USB_DESC_SUBTYPE_CDC_UNION,
            .bMasterInterface = 0,
            .bSlaveInterface0 = 1,
        },
    .ep_comm_int_2 =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_IN | 3),
            .bEndpointType = USB_ENDP_INT,
            .wMaxPacketSize = 8,
            .bInterval = USB_INTERVAL_FS_LS_INT(32),
        },

    // INTERFACE 3
    .itf_data_2 =
        {
            .bLength = sizeof(usb_interface_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_INTERFACE,
            .bInterfaceNumber = 3,
            .bAlternateSetting = 0x00,
            .bNumEndpoints = 2,
            .bInterfaceClass = USB_CLASS_CDC_DATA,
            .bInterfaceSubClass = USB_SUBCLASS_NONE,
            .bInterfaceProtocol = USB_PROTOCOL_NONE,
            .iInterface = 0,
        },
    .ep_data_out_2 =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_OUT | 4),
            .bEndpointType = USB_ENDP_BULK,
            .wMaxPacketSize = 64,
            .bInterval = 0x00,
        },
    .ep_data_in_2 =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_IN | 4),
            .bEndpointType = USB_ENDP_BULK,
            .wMaxPacketSize = 64,
            .bInterval = 0x00,
        },

    // ==========================================
    // MSC DEVICE. INTERFACE 4.
    // ==========================================
    .itf_msc =
        {
            .bLength = sizeof(usb_interface_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_INTERFACE,
            .bInterfaceNumber = 4,
            .bAlternateSetting = 0x00,
            .bNumEndpoints = 2,
            .bInterfaceClass = USB_CLASS_MASS_STORAGE,
            .bInterfaceSubClass = USB_SUBCLASS_SCSI,
            .bInterfaceProtocol = USB_PROTOCOL_MSC_BOT,
            .iInterface = 6,
        },
    .ep_msc_out =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_OUT | 5),
            .bEndpointType = USB_ENDP_BULK,
            .wMaxPacketSize = 64,
            .bInterval = 0x00,
        },
    .ep_msc_in =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_IN | 5),
            .bEndpointType = USB_ENDP_BULK,
            .wMaxPacketSize = 64,
            .bInterval = 0x00,
        },

    // ==========================================
    // CMSIS-DAP. INTERFACE 5
    // ==========================================
    .itf_custom =
        {
            .bLength = sizeof(usb_interface_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_INTERFACE,
            .bInterfaceNumber = 5,
            .bAlternateSetting = 0x00,
            .bNumEndpoints = 2,
            .bInterfaceClass = USB_CLASS_VENDOR_SPECIFIC,
            .bInterfaceSubClass = USB_SUBCLASS_NONE,
            .bInterfaceProtocol = USB_PROTOCOL_NONE,
            .iInterface = 7,
        },
    .ep_custom_out =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_OUT | 6),
            .bEndpointType = USB_ENDP_BULK,
            .wMaxPacketSize = 64,
            .bInterval = 0x00,
        },
    .ep_custom_in =
        {
            .bLength = sizeof(usb_endpoint_descriptor_t),
            .bDescriptorType = USB_DESC_TYPE_ENDPOINT,
            .bEndpointAddress = (USB_ENDP_IN | 6),
            .bEndpointType = USB_ENDP_BULK,
            .wMaxPacketSize = 64,
            .bInterval = 0x00,
        },
};

const usbx_string_framework_t usb_device_string_framework = {

    .string1 =
        {
            .langid = USB_LANG_EN_US,
            .str_id = 1,
            .len = GET_USB_STRING_LEN(STR_MANUFACTURER),
            .str = STR_MANUFACTURER,
        },

    .string2 =
        {
            .langid = USB_LANG_EN_US,
            .str_id = 2,
            .len = GET_USB_STRING_LEN(STR_PRODUCT),
            .str = STR_PRODUCT,
        },

    .string3 =
        {
            .langid = USB_LANG_EN_US,
            .str_id = 3,
            .len = GET_USB_STRING_LEN(STR_SERIAL),
            .str = STR_SERIAL,
        },

    .string4 =
        {
            .langid = USB_LANG_EN_US,
            .str_id = 4,
            .len = GET_USB_STRING_LEN(STR_COM1),
            .str = STR_COM1,
        },

    .string5 =
        {
            .langid = USB_LANG_EN_US,
            .str_id = 5,
            .len = GET_USB_STRING_LEN(STR_COM2),
            .str = STR_COM2,
        },

    .string6 =
        {
            .langid = USB_LANG_EN_US,
            .str_id = 6,
            .len = GET_USB_STRING_LEN(STR_MSC1),
            .str = STR_MSC1,
        },

    .string7 =
        {
            .langid = USB_LANG_EN_US,
            .str_id = 7,
            .len = GET_USB_STRING_LEN(STR_DBG1),
            .str = STR_DBG1,
        },
};

const usbx_language_id_framework_t usb_device_language_framework = {
    .langid = USB_LANG_EN_US};