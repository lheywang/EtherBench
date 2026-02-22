/**
 * @file 	configuration/storage.inc
 * @brief 	Sub configuration array to be seen as an MSC device (expose storage volumes)
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */
#pragma once

// ---------------------------------------------------------------------------
// MASS STORAGE CLASS (MSC) - Interface 4
// ---------------------------------------------------------------------------
#define DESC_MSC_LEN 23

#define DESC_MSC_BYTES \
	/* ---- */								\
	/* Interface 4 Descriptor (CONTROL) */	\
	/* ---- */								\
	0x09, /* bLength (9 bytes) */ 			\
	0x04, /* bDescriptorType (constant) */ 	\
	0x04, /* bInterfaceNumber */ 			\
	0x00, /* bAlternateSetting*/ 			\
	0x02, /* bNumEndpoints */				\
	0x08, /* bInterfaceClass (MSC)*/		\
	0x06, /* bInterfaceSubClass (SCSI) */	\
	0x50, /* bInterfaceProtocol (Bulk) */	\
	0x00, /* String index */				\
	/* EP5 DATA OUT */			 			\
	0x07, /* bLength (7 bytes) */			\
	0x05, /* bType (endpoint) */			\
	0x05, /* Endpoint (4) (OUT) */			\
	0x02, /* Endpoint type (BULK XFER) */	\
	0x40, 									\
	0x00, /* Max transfer size (64 byte) */	\
	0x00, /* String index (ignored) */		\
	/* EP2 DATA IN */			 			\
	0x07, /* bLength (7 bytes) */			\
	0x05, /* bType (endpoint) */			\
	0x85, /* Endpoint (133) (IN) */			\
	0x02, /* Endpoint type (BULK XFER) */	\
	0x40, 									\
	0x00, /* Max transfer size (64 byte) */	\
	0x00  /* String index (ignored) */

