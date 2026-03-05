/**
 * @file 	descriptors2.h
 * @brief 	Second version of the USB descriptors.
 *
 * @details This second version (and perhaps only one, if I deleted the previous one) is
 * based on compile time resolved symbols rather than live execution ones. This is
 * cleaner, and, a bit faster.
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	03/03/2026
 * @version 0.1
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                        VENDORS ID & SETTINGS
// ======================================================================
// Here we're using the ST ones, because the MCU is an ST one.
// Ensure to use the correct ones !
#define ST_VENDORID (0x0483)
#define ST_PRODUCTID (0x5740)
#define DEVICE_ID (0x0100)

// Here, we're defining values about the strings.
// This can make sure the compiler will work for us, when needed !
#define STR_MANUFACTURER "EtherBench Labs"
#define STR_PRODUCT "EtherBench v1"
#define STR_SERIAL "EB-2026-0001"

// Here we define what the task manager show as device names :
#define STR_COM1 "EtherBench TERMINAL"
#define STR_COM2 "EtherBench USART"
#define STR_MSC1 "EtherBench FLASH"
#define STR_DBG1 "EtherBench CMSIS-DAP Debugger"

// ======================================================================
//                              ENUMS
// ======================================================================
enum bDescriptorType {
    USB_DESC_TYPE_DEVICE = 0x01,
    USB_DESC_TYPE_CONFIGURATION = 0x02,
    USB_DESC_TYPE_STRING = 0x03,
    USB_DESC_TYPE_INTERFACE = 0x04,
    USB_DESC_TYPE_ENDPOINT = 0x05,
    USB_DESC_TYPE_DEVICE_QUALIFIER = 0x06,
    USB_DESC_TYPE_IAD = 0x0B,
    USB_DESC_TYPE_CDC_INTERFACE = 0x24,
    USB_DESC_TYPE_CDc_ENDPOINT = 0x25
};

enum bDescriptorSubType {
    USB_DESC_SUBTYPE_CDC_HEADER = 0x00,
    USB_DESC_SUBTYPE_CDC_MGNT = 0x01,
    USB_DESC_SUBTYPE_CDC_ACM = 0x02,
    USB_DESC_SUBTYPE_CDC_UNION = 0x06,
};

enum bcdUSB { USB_BCD_USB1_1 = 0x0110, USB_BCDC_USB2_0 = 0x0200 };

enum bDeviceClass {
    USB_CLASS_BASE = 0x00,
    USB_CLASS_AUDIO = 0x01,
    USB_CLASS_CDC = 0x02,
    USB_CLASS_HID = 0x03,
    USB_CLASS_PHYSICAL = 0x05,
    USB_CLASS_IMAGE = 0x06,
    USB_CLASS_PRINTER = 0x07,
    USB_CLASS_MASS_STORAGE = 0x08,
    USB_CLASS_HUB = 0x09,
    USB_CLASS_CDC_DATA = 0x0A,
    USB_CLASS_SMART_CARD = 0x0B,
    USB_CLASS_CONTENT_SECURITY = 0x0D,
    USB_CLASS_VIDEO = 0x0E,
    USB_CLASS_HEALTHCARE = 0x0F,
    USB_CLASS_AUDIO_VIDEO = 0x10,
    USB_CLASS_BILLBOARD = 0x11,
    USB_CLASS_USBC_BRIDGE = 0x12,
    USB_CLASS_BULK_DISPLAY = 0x13,
    USB_CLASS_MCTP = 0x14,
    USB_CLASS_DEV_I3C = 0x3C,
    USB_CLASS_DIAGNOSTIC = 0xDC,
    USB_CLASS_WIRELESS_CONTROLLER = 0xE0,
    USB_CLASS_MISC = 0xEF,
    USB_CLASS_APPLICATION_SPECIFIC = 0xFE,
    USB_CLASS_VENDOR_SPECIFIC = 0xFF
};

enum bDeviceSubClass {
    USB_SUBCLASS_NONE = 0x00,
    USB_SUBCLASS_MISC = 0x02,
    USB_SUBCLASS_CDC_ACM = 0x02,
    USB_SUBCLASS_SCSI = 0x06,
    USB_SUBCLASS_VENDOR = 0xFF
};

enum bDeviceProtcol {
    USB_PROTOCOL_NONE = 0x00,
    USB_PROTOCOL_MISC_IAD = 0x01,
    USB_PROTOCOL_CDC_AT = 0x01,
    USB_PROTOCOL_CDC_VENDOR = 0xFF,
    USB_PROTOCOL_MSC_BOT = 0x50,
    USB_PROTOCOL_VENDOR = 0xFF
};

enum bmAttributes {
    USB_ATTR_SELF_POWERED = 0x80,
    USB_ATTR_BUS_POWERED = 0xC0,
    USB_ATTR_RMT_WAKP = 0x09
};

enum bMaxPower { USB_PWR_100MA = 0x32, USB_PWR_500MA = 0xFA };

enum bEndpointType {
    USB_ENDP_CONTROL = 0x00,
    USB_ENDP_ISO = 0x01,
    USB_ENDP_BULK = 0x02,
    USB_ENDP_INT = 0x03,
    USB_ENDP_NONSYNC = 0x00,
    USB_ENDP_ASYNC = 0x5,
    USB_ENDP_ADAPT = 0x06,
    USB_ENDP_SYNC = 0x07,
    USB_ENDP_DATA = 0x00,
    USB_ENDP_FEEDBACK = 0x10,
    USB_ENDP_IMPLFEEDBACK = 0x20
};

enum bEndpointAddress {
    USB_ENDP_IN = 0x80,
    USB_ENDP_OUT = 0x00,
    USB_ENDP_EP0 = 0x00,
    USB_ENDP_EP1 = 0x01,
    USB_ENDP_EP2 = 0x02,
    USB_ENDP_EP3 = 0x03,
    USB_ENDP_EP4 = 0x04,
    USB_ENDP_EP5 = 0x05,
    USB_ENDP_EP6 = 0x06,
    USB_ENDP_EP7 = 0x07,
    USB_ENDP_EP8 = 0x08,
    USB_ENDP_EP9 = 0x09,
    USB_ENDP_EP10 = 0x0A,
    USB_ENDP_EP11 = 0x0B,
    USB_ENDP_EP12 = 0x0C,
    USB_ENDP_EP13 = 0x0D,
    USB_ENDP_EP14 = 0x0E,
    USB_ENDP_EP15 = 0x0F
};

enum wMaxPacketSize {
    USB_PACKET_SIZE_MASK = 0x03FF,
    USB_PACKET_FRAME_1XFER = 0x0000,
    USB_PACKET_FRAME_2XFER = 0x0500,
    USB_PACKET_FRAME_3XFER = 0x0600,
};

enum bLANGID { USB_LANG_EN_US = 0x0409, USB_LANG_GE_DE = 0x0407 };

#define USB_INTERVAL_FS_HS_ISO(x) ((x & 0x1F) | 0x01)
#define USB_INTERVAL_FS_LS_INT(x) ((x & 0xFF))
#define USB_INTERVAL_HS_INT(x)                                                           \
    USB_INTERVAL_FS_HS_ISO(x) // It's the same, prevent from copy pasting code.
#define USB_INTERVAL_HS_BULK_CTRL(x)                                                     \
    USB_INTERVAL_FS_LS_INT(x) // It's the same, prevent from copy pasting code.

#define UINT16_TO_LE(x) (((x & 0xFF00) >> 8) | (x & 0x00FF) << 8)
#define GET_TOTAL_LE_SIZE(x) UINT16_TO_LE(x)

#define USB_CDC_bCDC (0x1001)

#define GET_USB_STRING_LEN(STR) (sizeof(STR) - 1)

// ======================================================================
//                           MASTER STRUCTS
// ======================================================================

/**
 * @brief This struct define the usb device descriptor form.
 */
typedef struct __attribute__((packed)) {
    uint8_t bLength;            ///< bLength (18 bytes)
    uint8_t bDescriptorType;    ///< bDescriptorType (USB_DESC_TYPE_DEVICE)
    uint16_t bcdUSB;            ///< bcdUSB
    uint8_t bDeviceClass;       ///< bDeviceClass
    uint8_t bDeviceSubClass;    ///< bDeviceSubClass
    uint8_t bDeviceProtocol;    ///< bDeviceProtocol
    uint8_t bMaxPacketSize0;    ///< bMaxPacketSize0
    uint16_t idVendor;          ///< idVendor
    uint16_t idProduct;         ///< idProduct
    uint16_t bcdDevice;         ///< bcdDevice
    uint8_t iManufacturer;      ///< iManufacturer
    uint8_t iProduct;           ///< iProduct
    uint8_t iSerialNumber;      ///< iSerialNumber
    uint8_t bNumConfigurations; ///< bNumConfigurations
} usb_device_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;             ///< bLength (9 bytes)
    uint8_t bDescriptorType;     ///< bDescriptorType (USB_DESC_TYPE_CONFIGURATION)
    uint16_t wTotalLength;       ///< wTotalLength (16 bits, LE)
    uint8_t bNumInterfaces;      ///< bNumInterfaces
    uint8_t bConfigurationValue; ///< bConfigurationValue
    uint8_t iConfiguration;      ///< iConfiguration (or 0x00)
    uint8_t bmAttributes;        ///< Attributes (power source ...)
    uint8_t bMaxPower;           ///< bMaxPower (In 2 mA steps)
} usb_config_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;            ///< bLength (9 bytes)
    uint8_t bDescriptorType;    ///< bDescriptorType (USB_DESC_TYPE_INTERFACE)
    uint8_t bInterfaceNumber;   ///< bInterfaceNumber
    uint8_t bAlternateSetting;  ///< bAlternateSetting
    uint8_t bNumEndpoints;      ///< bNumEndpoints
    uint8_t bInterfaceClass;    ///< bInterfaceClass
    uint8_t bInterfaceSubClass; ///< bInterfaceSubClass
    uint8_t bInterfaceProtocol; ///< bInterfaceProtocol
    uint8_t iInterface;         ///< iInterface
} usb_interface_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;          ///< bLength (7 bytes)
    uint8_t bDescriptorType;  ///< bType (USB_DESC_TYPE_ENDPOINT)
    uint8_t bEndpointAddress; ///< bEndpointAddress
    uint8_t bEndpointType;    ///< bEndpointType
    uint16_t wMaxPacketSize;  ///< wMaxPacketSize
    uint8_t bInterval;        ///< bInterval
} usb_endpoint_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;           ///< bLength
    uint8_t bDescriptorType;   ///< bDescriptorType
    uint8_t bFirstInterface;   ///< bFirstInterface
    uint8_t bInterfaceCount;   ///< bInterfaceCount
    uint8_t bFunctionClass;    ///< bFunctionClass
    uint8_t bFunctionSubClass; ///< bFunctionSubClass
    uint8_t bFunctionProtocol; ///< bFunctionProtocol
    uint8_t iFunction;         ///< iFunction
} usb_iad_descriptor_t;

// ======================================================================
//                              STRINGS DESCRIPTORS
// ======================================================================

typedef struct __attribute__((packed)) {
    uint8_t bLength;         ///< bLength
    uint8_t bDescriptorType; ///< bDescriptorType (USB_DESC_TYPE_STRING)
    uint16_t wLangID;        ///< wLangID (max 1).
} usb_string_langid_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;         ///< bLength
    uint8_t bDescriptorType; ///< bDescriptorType (USB_DESC_TYPE_STRING)
} usb_string_descriptor_header_t;

// ======================================================================
//                              CLASS SPECIFIC HEADERS
// ======================================================================

typedef struct __attribute__((packed)) {
    uint8_t bLength;            ///< bLength
    uint8_t bDescriptorType;    ///< bDescriptorType
    uint8_t bDescriptorSubtype; ///< bDescriptorSubtype
    uint16_t bcdCDC;            ///< bcdCDC
} cdc_header_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;            ///< bLength
    uint8_t bDescriptorType;    ///< bDescriptorType
    uint8_t bDescriptorSubtype; ///< bDescriptorSubtype
    uint8_t bmCapabilities;     ///< bmCapabilities
    uint8_t bDataInterface;     ///< bDataInterface
} cdc_call_mgmt_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;            ///< bLength
    uint8_t bDescriptorType;    ///< bDescriptorType
    uint8_t bDescriptorSubtype; ///< bDescriptorSubtype
    uint8_t bmCapabilities;     ///< bmCapabilities
} cdc_acm_descriptor_t;

typedef struct __attribute__((packed)) {
    uint8_t bLength;            ///< bLength
    uint8_t bDescriptorType;    ///< bDescriptorType
    uint8_t bDescriptorSubtype; ///< bDescriptorSubtype
    uint8_t bMasterInterface;   ///< bMasterInterface
    uint8_t bSlaveInterface0;   ///< bSlaveInterface0
} cdc_union_descriptor_t;

// ======================================================================
//                   THE COMPOSITE TREE (CDC-ACM)
// ======================================================================
/**
 * @brief That's the whole configuration. GCC does the heavy lifting by giving us
 * everything we need !
 */
typedef struct __attribute__((packed)) {
    usb_device_descriptor_t device;
    usb_config_descriptor_t config;

    // ==========================================
    // COM PORT (TERMINAL). INTERFACES 0 and 1
    // ==========================================
    usb_iad_descriptor_t iad_cdc_1;

    usb_interface_descriptor_t itf_comm_1;
    cdc_header_descriptor_t cdc_hdr_1;
    cdc_call_mgmt_descriptor_t cdc_mgmt_1;
    cdc_acm_descriptor_t cdc_acm_1;
    cdc_union_descriptor_t cdc_union_1;
    usb_endpoint_descriptor_t ep_comm_int_1;

    usb_interface_descriptor_t itf_data_1;
    usb_endpoint_descriptor_t ep_data_out_1;
    usb_endpoint_descriptor_t ep_data_in_1;

    // ==========================================
    // COM PORT (USB-UART). INTERFACES 2 and 3
    // ==========================================
    usb_iad_descriptor_t iad_cdc_2;

    usb_interface_descriptor_t itf_comm_2;
    cdc_header_descriptor_t cdc_hdr_2;
    cdc_call_mgmt_descriptor_t cdc_mgmt_2;
    cdc_acm_descriptor_t cdc_acm_2;
    cdc_union_descriptor_t cdc_union_2;
    usb_endpoint_descriptor_t ep_comm_int_2;

    usb_interface_descriptor_t itf_data_2;
    usb_endpoint_descriptor_t ep_data_out_2;
    usb_endpoint_descriptor_t ep_data_in_2;

    // ==========================================
    // MSC DEVICE. INTERFACE 4.
    // ==========================================
    // Commented OUT in the final version. MSC won't be used.
    // usb_interface_descriptor_t itf_msc;
    // usb_endpoint_descriptor_t ep_msc_out;
    // usb_endpoint_descriptor_t ep_msc_in;

    // ==========================================
    // CMSIS-DAP. INTERFACE 5
    // ==========================================
    usb_interface_descriptor_t itf_custom;
    usb_endpoint_descriptor_t ep_custom_out;
    usb_endpoint_descriptor_t ep_custom_in;

} usb_composite_configuration_tree_t;

// ======================================================================
//                      STRINGS AND LANGUAGES FRAMEWORKS
// ======================================================================

typedef struct __attribute__((packed)) {

    struct __attribute__((packed)) {
        uint16_t langid;
        uint8_t str_id;
        uint8_t len;
        char str[GET_USB_STRING_LEN(STR_MANUFACTURER)];
    } string1;

    struct __attribute__((packed)) {
        uint16_t langid;
        uint8_t str_id;
        uint8_t len;
        char str[GET_USB_STRING_LEN(STR_PRODUCT)];
    } string2;

    struct __attribute__((packed)) {
        uint16_t langid;
        uint8_t str_id;
        uint8_t len;
        char str[GET_USB_STRING_LEN(STR_SERIAL)];
    } string3;

    struct __attribute__((packed)) {
        uint16_t langid;
        uint8_t str_id;
        uint8_t len;
        char str[GET_USB_STRING_LEN(STR_COM1)];
    } string4;

    struct __attribute__((packed)) {
        uint16_t langid;
        uint8_t str_id;
        uint8_t len;
        char str[GET_USB_STRING_LEN(STR_COM2)];
    } string5;

    struct __attribute__((packed)) {
        uint16_t langid;
        uint8_t str_id;
        uint8_t len;
        char str[GET_USB_STRING_LEN(STR_MSC1)];
    } string6;

    struct __attribute__((packed)) {
        uint16_t langid;
        uint8_t str_id;
        uint8_t len;
        char str[GET_USB_STRING_LEN(STR_DBG1)];
    } string7;

} usbx_string_framework_t;

typedef struct __attribute__((packed)) {
    uint16_t langid;
} usbx_language_id_framework_t;

// ======================================================================
//                              VARIABLES
// ======================================================================
extern const usb_composite_configuration_tree_t usb_device_desc;
extern const usbx_string_framework_t usb_device_string_framework;
extern const usbx_language_id_framework_t usb_device_language_framework;

#ifdef __cplusplus
}
#endif