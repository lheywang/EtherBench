/**
 * @file 	configuration/cmsis.inc
 * @brief 	Sub configuration array, to be seen as CMSIS debugger
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */
#pragma once

// ---------------------------------------------------------------------------
// CUSTOM (CMSIS-DAP) - Interface 5
// ---------------------------------------------------------------------------
#define DESC_CMSIS_LEN 23

#define DESC_CMSIS_BYTES \
	/* ---- */								\
	/* Interface 4 Descriptor (CONTROL) */	\
	/* ---- */								\
	0x09, /* bLength (9 bytes) */ 			\
	0x04, /* bDescriptorType (constant) */ 	\
	0x05, /* bInterfaceNumber */ 			\
	0x00, /* bAlternateSetting*/ 			\
	0x02, /* bNumEndpoints */				\
	0xFF, /* bInterfaceClass (MSC)*/		\
	0x00, /* bInterfaceSubClass (SCSI) */	\
	0x00, /* bInterfaceProtocol (Bulk) */	\
	0x04, /* String index */				\
	/* EP6 DATA OUT */			 			\
	0x07, /* bLength (7 bytes) */			\
	0x05, /* bType (endpoint) */			\
	0x06, /* Endpoint (6) (OUT) */			\
	0x02, /* Endpoint type (BULK XFER) */	\
	0x40, 									\
	0x00, /* Max transfer size (64 byte) */	\
	0x00, /* String index (ignored) */		\
	/* EP2 DATA IN */			 			\
	0x07, /* bLength (7 bytes) */			\
	0x05, /* bType (endpoint) */			\
	0x86, /* Endpoint (134) (IN) */			\
	0x02, /* Endpoint type (BULK XFER) */	\
	0x40, 									\
	0x00, /* Max transfer size (64 byte) */	\
	0x00  /* String index (ignored) */
