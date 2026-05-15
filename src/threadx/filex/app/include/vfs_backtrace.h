/**
 * @file    vfs_backtrace.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-05-15
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries

// HAL
#include "stm32h5xx.h"

// STD
#include <stdint.h>

// ======================================================================
//                               DEFINES
// ======================================================================
// Number of used backtrace entries
#define MAX_BACKTRACE_ENTRY 512

// Configurations
#define BACKTRACE_ENTRY_PAGE_ADDR 0x01FF ///< 10 LSB are the page address. 600 < 1024.
#define BACKTRACE_ENTRY_STATE     0x8000 ///< MSB is the state. Set
#define BACKTRACE_ENTRY_NEW       0x4000 ///< 2 MSB is the new. Set to 0 after the first read.

// Entries values
#define BACKTRACE_USED_ENTRY   0 ///< Set to 0 once an entry has been added.
#define BACKTRACE_UNUSED_ENTRY 1 ///< Reset to 1 when the block is erased.
#define BACKTRACE_NEW_ENTRY    1 ///< Let as 1 for the first write. Marked as new (not read).
#define BACKTRACE_OLD_ENTRY    0 ///< Set to 0 once this entry has been read. Could be cleanup after.

// ======================================================================
//                           HELPER FUNCTIONS
// ======================================================================
inline static const uint16_t GET_ENTRY_STATUS(uint16_t entry) { return entry & BACKTRACE_ENTRY_STATE; }
inline static const uint16_t GET_ENTRY_ADDRESS(uint16_t entry) { return entry & BACKTRACE_ENTRY_PAGE_ADDR; }
inline static const uint16_t GET_ENTRY_NEW(uint16_t entry) { return entry & BACKTRACE_ENTRY_NEW; }

// ======================================================================
//                              STRUCTURE
// ======================================================================
/**
 * @brief This structure hold the entire device config, into the 2048
 *        bytes page. Placed on the logical sector 0, by LevelX. May
 *        refer to more advanced configs internally.
 *
 * @return typedef struct
 */
typedef struct __attribute__((packed)) {

    uint64_t timestamp;
    uint32_t core_id;

    struct __attribute__((packed)) {
        uint32_t r[12];
        uint32_t msp;
        uint32_t psp;
        uint32_t lr;
        uint32_t pc;
        uint32_t xpsr;
        uint32_t apsr;
        uint32_t ipsr;
        uint32_t epsr;
        uint32_t primask;
        uint32_t faultmask;
        uint32_t basepri;
        uint32_t control;
        uint32_t psplim;
        uint32_t msplim;
    } registers;

} BACKTRACE_ENTRY;