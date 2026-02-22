/**
 * @file 	configuration/serial.inc
 * @brief 	Sub configuration array to be seen as a serial port
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */
#pragma once

// ---------------------------------------------------------------------------
// Main serial interface
// ---------------------------------------------------------------------------
#define DESC_CDC_MUX_LEN 66

#define DESC_CDC_MUX_BYTES \
    /* IAD */ \
    0x08, 0x0B, 0x00, 0x02, 0x02, 0x02, 0x01, 0x00, \
							/* ---- */								\
    						/* Interface 0 Descriptor */ 			\
							/* ---- */								\
    						0x09, /* bLength (9 bytes) */ 			\
							0x04, /* bDescriptorType (constant) */ 	\
							0x00, /* bInterfaceNumber */ 			\
							0x00, /* bAlternateSetting*/ 			\
							0x01, /* bNumEndpoints */				\
							0x02, /* bInterfaceClass */				\
							0x02, /* bInterfaceSubClass */			\
							0x01, /* bInterfaceProtocol */			\
							0x00, /* iInterface */					\
							/* ---- */								\
							/* ENDPOINTS DESCRIPTIONS */			\
							/* ---- */								\
    0x05, 0x24, 0x00, 0x10, 0x01, \
    0x05, 0x24, 0x01, 0x00, 0x01, \
    0x04, 0x24, 0x02, 0x02, \
    0x05, 0x24, 0x06, 0x00, 0x01, \
    /* EP1 IN */ \
    0x07, 0x05, 0x81, 0x03, 0x08, 0x00, 0xFF, \
    /* Interface 1 */ \
    0x09, 0x04, 0x01, 0x00, 0x02, 0x0A, 0x00, 0x00, 0x00, \
    /* EP2 OUT & IN */ \
    0x07, 0x05, 0x02, 0x02, 0x40, 0x00, 0x00, \
    0x07, 0x05, 0x82, 0x02, 0x40, 0x00, 0x00

