/**
 * @file    logger.h
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Header to define the base a logger module, which handle a fast,
 * 			DMA based IO, from high level functions.
 *
 * @version 0.1
 * @date    2026-03-01
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local library
#include "app_threadx.h"

// STD
#include <stdint.h>

// ======================================================================
//                              DEFINES
// ======================================================================
/*
 * We add a default name for this module, as it's used as a module name for
 * advanced logging.
 */
#ifndef LOG_MODULE
#define LOG_MODULE "DEFAULT"
#endif

/*
 * Configuring the logger.
 */
#define LOG_BUFFER_SIZE 1024     ///< The buffer size used by the logger module.
#define LOG_BUFFER_THRESHOLD 768 ///< The threshold at which the buffer will be emptied.

#define LOG_MAX_LENGTH 128 ///< The size of the maximal line that can be sent in a single call.

// ======================================================================
//                              MACROS
// ======================================================================
/**
 * @brief 	Send a request to log something.
 *			Logs are formatted as : [ LOG_MODULE ] (file:line)
 *          "message".
 *          Newlines aren't needed, they're automatically added to the buffer.
 *
 * @warning 	Logs can't be longer than LOG_MAX_LENGTH characters, newline
 *included.
 *
 * @param[in]	format 	The format string
 * @param[in] 	... 	The list of variable arguments.
 */
#define LOG(format, ...) add_log(LOG_MODULE, __FILE__, __LINE__, format, ##__VA_ARGS__)

// ======================================================================
//                              FUNCTIONS
// ======================================================================

/**
 * @brief 	Create the background logging task, charged to handle the IO.
 * 			IO are triggered with DMA, to save CPU cycles, when the
 * buffer is full enough
 * 			(> 75%), or on timeout of a semaphore.
 * 			This enable an efficient logging without saturating CPU.
 *
 * @param[in] 	arg 	Unused.
 *
 * @return		void (never return).
 */
void logger_task(ULONG arg);

/**
 * @brief 	Function used to append logs to the internal buffer, and track
 * the size when needed. Used within the LOG(...) macro to add logs. Will
 * trigger the task when a buffer need to be sent.
 *
 * @param[in]	*module 	The module name to be shown
 * @param[in] 	*file		The file from which this function is called.
 * Filled by GCC using __FILE__ macro.
 * @param[in] 	line 		The line number from which this function is
 * called. Filled by GCC using __LINE__ macro.
 * @param[in]	format 		The format string, as any std function
 * (printf...).
 * @param[in] 	... 		The ##__VA_ARGS__ to be passed to the printf
 * function.
 */
uint32_t add_log(const char *module, const char *file, const int line, const char *format, ...);

/**
 * @brief 	The function called by the ISR handle, when a transmission has
 * finished. Will clear the buffer, and reset some variables to 0.
 */
void dma_tx_callback();

#ifdef __cplusplus
}
#endif
