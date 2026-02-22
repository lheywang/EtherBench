/**
 * @file 	device/descriptor.inc
 * @brief 	Main device descriptor by array for the USB enumeration.
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */
#pragma once

// ---------------------------------------------------------------------------
// DEVICE DESCRIPTOR
// ---------------------------------------------------------------------------
#define DESC_DEV_LEN 18

#define DESC_DEV_BYTES	\
	0x12,       /* bLength (18 bytes) */ 											\
	0x01,       /* bDescriptorType (Device) */ 										\
	0x00, 0x02, /* bcdUSB (USB 2.0) */												\
	0xEF,       /* bDeviceClass (Miscellaneous - Required for IAD Composites) */ 	\
	0x02,       /* bDeviceSubClass (Common Class) */								\
	0x01,       /* bDeviceProtocol (Interface Association) */						\
	0x40,       /* bMaxPacketSize0 (64 bytes for EP0) */							\
	0x83, 0x04, /* idVendor (STMicroelectronics 0x0483) */							\
	0x40, 0x57, /* idProduct (Virtual Com Port 0x5740) */							\
	0x00, 0x02, /* bcdDevice (Release 2.00) */										\
	0x01,       /* iManufacturer (String Index 1) */								\
	0x02,       /* iProduct (String Index 2) */										\
	0x03,       /* iSerialNumber (String Index 3) */								\
	0x01        /* bNumConfigurations (1) */
