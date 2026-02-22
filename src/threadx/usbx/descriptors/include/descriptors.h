/**
 * @file 	descriptors.h
 * @brief 	Global USB Device descriptors configuration
 *
 * @author 	l.heywang <leonard.heywang@proton.me>
 * @date 	22/02/2026
 * @version 0.1
 */

#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
#include <stdint.h>

// ======================================================================
// DEVICE DESCRIPTOR
// ======================================================================
/**
 * @brief 	Device descriptor for the whole USB device
 */
extern const uint8_t device_descriptor[];

/**
 * @brief 	Configuration descriptor for all the interfaces (2x VCOM, 1x MSC, 1x CUSTOM).
 */
extern const uint8_t configuration_descriptor[];

/**
 * @brief 	Languages framework definitions (EN-US)
 */
extern const uint8_t language_id_framework[];

/*
 * @brief	Strings constants for the manufacturer, name, and so on...
 */
extern const uint8_t string_framework[];

// ======================================================================
// DEFINES FOR LENGTH
// ======================================================================
// We use macros, to prevent from hardcoding it
#ifndef DEVICE_DESCRIPTOR_LEN
#define DEVICE_DESCRIPTOR_LEN (sizeof(device_descriptor))
#endif

#ifndef CONFIGURATION_DESCRIPTOR_LEN
#define CONFIGURATION_DESCRIPTOR_LEN (sizeof(configuration_descriptor))
#endif

#ifndef LANGUAGE_ID_FRAMEWORK_LEN
#define LANGUAGE_ID_FRAMEWORK_LEN (sizeof(language_id_framework))
#endif

#ifndef STRING_FRAMEWORK_LEN
#define STRING_FRAMEWORK_LEN (sizeof(string_framework))
#endif



