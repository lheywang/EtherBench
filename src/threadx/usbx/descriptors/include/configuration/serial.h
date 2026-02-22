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
	/* ---- */								\
	/* IAD */ 								\
	/* ---- */ 								\
	0x08, /* bLength (8 bytes) */			\
	0x0B, /* bType (IAD) */					\
	0x00, /* First interface Number */		\
	0x02, /* Number of interfaces */		\
	0x02, /* Class (Communication) */		\
	0x02, /* Subclass (ACM)*/				\
	0x01, /* Protocol (AT Commands) */		\
	0x00, /* */								\
											\
	/* ---- */								\
	/* Interface 0 Descriptor (CONTROL) */	\
	/* ---- */								\
	0x09, /* bLength (9 bytes) */ 			\
	0x04, /* bDescriptorType (constant) */ 	\
	0x00, /* bInterfaceNumber */ 			\
	0x00, /* bAlternateSetting*/ 			\
	0x01, /* bNumEndpoints */				\
	0x02, /* bInterfaceClass */				\
	0x02, /* bInterfaceSubClass */			\
	0x01, /* bInterfaceProtocol */			\
	0x00, /* String index */				\
	/* ---- */								\
	/* CDC HEADER */						\
	/* ---- */								\
	0x05, 0x24, 0x00, 0x10, 0x01, 			\
	0x05, 0x24, 0x01, 0x00, 0x01, 			\
	0x04, 0x24, 0x02, 0x02, 				\
	0x05, 0x24, 0x06, 0x00, 0x01, 			\
	/* EP1 INTERRUPT CONTROL */ 			\
	0x07, /* bLength (7 bytes) */			\
	0x05, /* bType (endpoint) */			\
	0x81, /* Endpoint address + direction */\
	0x03, /* Endpoint type (interrupt) */   \
	0x08, 									\
	0x00, /* Data size (8 Bytes, LE) */		\
	0xFF, /* Polling interval (255 ms) */	\
											\
	/* ---- */								\
	/* Interface 1 Descriptor (DATA XFER) */\
	/* ---- */								\
	/* EP2 DATA */	 						\
	0x09, /* bLength (9 bytes) */			\
	0x04, /* bType (interface) */			\
	0x01, /* bInterface (1) */				\
	0x00, /* Alternate settings (0) */		\
	0x02, /* Number of Endpoints */ 		\
	0x0A, /* Class = CDC Data */			\
	0x00, /* Subclass (0) */				\
	0x00, /* Protocol (0) */				\
	0x00, /* String index (0) */			\
	/* EP2 DATA OUT */			 			\
	0x07, /* bLength (7 bytes) */			\
	0x05, /* bType (endpoint) */			\
	0x02, /* Endpoint (2) (OUT) */			\
	0x02, /* Endpoint type (BULK XFER) */	\
	0x40, 									\
	0x00, /* Max transfer size (64 byte) */	\
	0x00, /* String index (ignored) */		\
	/* EP2 DATA IN */			 			\
	0x07, /* bLength (7 bytes) */			\
	0x05, /* bType (endpoint) */			\
	0x82, /* Endpoint (130) (OUT) */		\
	0x02, /* Endpoint type (BULK XFER) */	\
	0x40, 									\
	0x00, /* Max transfer size (64 byte) */	\
	0x00  /* String index (ignored) */

