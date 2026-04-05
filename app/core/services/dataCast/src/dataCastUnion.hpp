/**
 * @file    dataCastUnion.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the casting union used to convert from types to types faster
 * @version 0.1
 * @date    2026-04-05
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// =============================================================
// INCLUDES
// =============================================================
// Qt
#include <QString>

// STD
#include <stdfloat>
#include <stdint>

// =============================================================
// MACRO PLAY
// =============================================================
#ifndef __SIZEOF_INT128__
#pragma message "128 bits integer aren't defined. They'll be disabled (constant to 0)."
#endif

namespace EtherBench::Services {

// =============================================================
// CONSTEXPR
// =============================================================
// Configure how many bytes are we handling in a single cast
constexpr uint32_t byte_length = 32;

// Compute the size of some values
// output
constexpr uint32_t U8_COUNT = byte_length / sizeof(uint8_t);
constexpr uint32_t I8_COUNT = byte_length / sizeof(int8_t);

constexpr uint32_t U16_COUNT = byte_length / sizeof(uint16_t);
constexpr uint32_t I16_COUT = byte_length / sizeof(int16_t);

constexpr uint32_t U32_COUNT = byte_length / sizeof(uint32_t);
constexpr uint32_t I32_COUNT = byte_length / sizeof(int32_t);

constexpr uint32_t U64_COUNT = byte_length / sizeof(uint64_t);
constexpr uint32_t I64_COUNT = byte_length / sizeof(int64_t);

constexpr uint32_t U128_COUNT = byte_length / sizeof(__int128_t);
constexpr uint32_t I128_COUNT = byte_length / sizeof(__uint128_t);

constexpr uint32_t F16_COUNT = byte_length / sizeof(float16_t);
constexpr uint32_t F16B_COUNT = byte_length / sizeof(bfloat16_t);
constexpr uint32_t F32_COUNT = byte_length / sizeof(float32_t);
constexpr uint32_t F64_COUNT = byte_length / sizeof(float64_t);
constexpr uint32_t F128_COUNT = byte_length / sizeof(float128_t);

// =============================================================
// UNIONS
// =============================================================

union dataCastUnion {

    // "input"
    uint8_t in[byte_length];

    // output
    uint8_t u8[U8_COUNT];
    int8_t i8[I8_COUNT];

    uint16_t u16[U16_COUNT];
    int16_t i16[I16_COUNT];

    uint32_t u32[U32_COUNT];
    int32_t i32[I32_COUNT];

    // 24 bits not handled --> To do in software

    uint64_t u64[U64_COUNT];
    int64_t i64[I64_COUNT];

#ifdef __SIZEOF_INT128__
    __int128_t u128[U128_COUNT];
    __uint128_t i128[I128_COUNT];
#endif

    float16_t f16[F16_COUNT];
    bfloat16_t f16b[F16B_COUNT];
    float32_t f32[F32_COUNT];
    float64_t f64[F64_COUNT];
    float128_t f128[F128_COUNT];
};

} // namespace EtherBench::Services
