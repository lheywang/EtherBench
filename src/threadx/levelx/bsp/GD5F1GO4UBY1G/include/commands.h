/**
 * @file    commands.h
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define the standard GD5F1GO4UBY1G commands.
 * @version 0.1
 * @date    2026-04-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ======================================================================
//                         DEFINES (DEVICE)
// ======================================================================
// Pages
#define GD25_PAGE_SIZE 2048
#define GD25_PAGE_OOB 128
#define GD25_PAGE_OOD_ADDR (GD25_PAGE_SIZE)
#define GD25_PAGE_TOTAL (GD25_PAGE_SIZE + GD25_PAGE_OOB)

// Blocks
#define GD25_BLOCK_PAGES 64
#define GD25_BLOCK_SIZE (GD25_PAGE_SIZE * GD25_BLOCK_PAGES)
#define GD25_BLOCK_TOTAL (GD25_PAGE_TOTAL * GD25_BLOCK_PAGES)

// Device
#define GD25_BLOCK_COUNT_NORMAL 1024
#define GD25_BLOCK_COUNT_MINIMAL 1004
#define GD25_SIZE_NORMAL (GD25_BLOCK_SIZE * GD25_BLOCK_COUNT_NORMAL)
#define GD25_SIZE_TOTAL_NORMAL (GD25_BLOCK_TOTAL * GD25_BLOCK_COUNT_NORMAL)
#define GD25_SIZE_MINIMAL (GD25_BLOCK_SIZE * GD25_BLOCK_COUNT_MINIMAL)
#define GD25_SIZE_TOTAL_MINIMAL (GD25_BLOCK_TOTAL * GD25_BLOCK_COUNT_MINIMAL)

// ======================================================================
//                         DEFINES (COMMANDS)
// ======================================================================
// Write management
#define GD25_WRITE_ENABLE 0x06
#define GD25_WRITE_DISABLE 0x04

// Features
#define GD25_GET_FEATURES 0x0F
#define GD25_SET_FEATURES 0x1F

// Read
#define GD25_READ_TO_CACHE 0x13
#define GD25_READ_FROM_CACHE 0x03
#define GD25_READ_FROM_CACHE_ 0x0B
#define GD25_READ_FROM_CACHE_X2 0x3B
#define GD25_READ_FROM_CACHE_X4 0x6B
#define GD25_READ_FROM_CACHE_DIO 0xBB
#define GD25_READ_FROM_CACHE_QIO 0xEB

// ID
#define GD25_READ_ID 0x9F

// Write
#define GD25_PROGRAM_LOAD 0x02
#define GD25_PROGRAM_LOAD_X4 0x32
#define GD25_PROGRAM_EXECUTE 0x10
#define GD25_LOAD_RANDOM_DATA 0x84
#define GD25_LOAD_RANDOM_DATA_X4 0xC4
#define GD25_LOAD_RANDOM_DATA_X4_ 0x34
#define GD25_LOAD_RANDOM_DATA_QIO 0x72

// Erase
#define GD25_BLOCK_ERASE 0xD8

// Reset
#define GD25_RESET 0xFF

// ======================================================================
//                         DEFINES (FEATURES REGISTERS)
// ======================================================================
// Registers
#define GD25_FEATURE_REG_PROTECTION 0xA0
#define GD25_FEATURE_REG_FEATURE_1 0xB0
#define GD25_FEATURE_REG_STATUS_1 0xC0
#define GD25_FEATURE_REG_FEATURE_2 0xD0
#define GD25_FEATURE_REG_STATUS_2 0xF0

// ======================================================================
//                         DEFINES (FEATURES BITS)
// ======================================================================
// Protection register
#define GD25_FEATURE_BIT_BRWD (1 << 7)
#define GD25_FEATURE_BIT_BP2 (1 << 5)
#define GD25_FEATURE_BIT_BP1 (1 << 4)
#define GD25_FEATURE_BIT_BP0 (1 << 3)
#define GD25_FEATURE_BIT_INV (1 << 2)
#define GD25_FEATURE_BIT_CMP (1 << 1)

// Feature_1 register
#define GD25_FEATURE_BIT_OTP_PRT (1 << 7)
#define GD25_FEATURE_BIT_OPT_EN (1 << 6)
#define GD25_FEATURE_BIT_ECC_EN (1 << 4)
#define GD25_FEATURE_BIT_QE (1 << 0)

// Status_1 register
#define GD25_FEATURE_BIT_ECCS1 (1 << 5)
#define GD25_FEATURE_BIT_ECCS0 (1 << 4)
#define GD25_FEATURE_BIT_P_FAIL (1 << 3)
#define GD25_FEATURE_BIT_E_FAIL (1 << 2)
#define GD25_FEATURE_BIT_WEL (1 << 1)
#define GD25_FEATURE_BIT_OIP (1 << 0)

// Feature_2 register
#define GD25_FEATURE_BIT_DS_S1 (1 << 6)
#define GD25_FEATURE_BIT_DS_S2 (1 << 5)

// Status_2 register
#define GD25_FEATURE_BIT_ECCSE1 (1 << 5)
#define GD25_FEATURE_BIT_ECCSE0 (1 << 4)
