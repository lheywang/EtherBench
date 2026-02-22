/**
 * @file 	descriptors.c
 * @brief 	Global USB Device descriptors configuration
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "descriptors.h"

// Local libraries
#include "device/device.h"
#include "configuration/cmsis.h"
#include "configuration/serial.h"
#include "configuration/storage.h"
#include "configuration/terminal.h"

// STD
#include <stdint.h>

// ======================================================================
// DEVICE DESCRIPTOR
// ======================================================================
const uint8_t device_descriptor[] = {
	DESC_DEV_BYTES
};

// ======================================================================
// CONFIGURATION DESCRIPTOR LENGTH MATH
// ======================================================================
#define SIZE_HEADER  9
#define TOTAL_LEN    (SIZE_HEADER + DESC_CMSIS_LEN + DESC_CDC_MUX_LEN + DESC_MSC_LEN + DESC_CDC_TRM_LEN)

// ======================================================================
// 3. MASTER CONFIGURATION ARRAY
// ======================================================================
const uint8_t configuration_descriptor[] = {
    // --- Header ---
    0x09, 					/* bLength (9 bytes) */
	0x02, 					/* bDescriptorType (Configuration) */
    (TOTAL_LEN & 0xFF),
	(TOTAL_LEN >> 8), 		/* wTotalLength (16 bits, LE) */
    0x06, 					/* bNumInterfaces (6) */
    0x01,					/* bConfigurationValue (1) */
	0x00, 					/* iConfiguration (0 = ignored) */
	0x80, 					/* Bus powered */
	0xFF,					/* bMaxPower (255 * 2 mA = 500 mA)*/

    // --- Interfaces pasted sequentially ---
    DESC_CDC_MUX_BYTES,
    DESC_CDC_TRM_BYTES,
    DESC_MSC_BYTES,
    DESC_CMSIS_BYTES
};

// ======================================================================
// STRINGS & LANGUAGE ID
// ======================================================================
const uint8_t language_id_framework[] = {
    0x04, 0x03, 0x09, 0x04
};

const uint8_t string_framework[] = {
    // Index 1: Manufacturer
    0x01, 0x0F,
    'E', 't', 'h', 'e', 'r', 'B', 'e', 'n', 'c', 'h', ' ', 'L', 'a', 'b', 's',

    // Index 2: Product Name
    0x02, 0x15,
    'E', 't', 'h', 'e', 'r', 'B', 'e', 'n', 'c', 'h',

    // Index 3: Serial Number
    0x03, 0x0B,
    'E', 'B', '-', '2', '0', '2', '6', '-', '0', '0', '1',

    // Index 4: CMSIS-DAP String
    0x04, 0x17,
    'E', 't', 'h', 'e', 'r', 'B', 'e', 'n', 'c', 'h', ' ', 'C', 'M', 'S', 'I', 'S', '-', 'D', 'A', 'P', ' ', 'v', '1'
};

