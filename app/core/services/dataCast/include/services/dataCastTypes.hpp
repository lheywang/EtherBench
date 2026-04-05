/**
 * @file    dataCastTypes.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the dataCast result type.
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

// =============================================================
// STRUCTS
// =============================================================
namespace EtherBench::Services {

struct dataCastResult {

    // Little endian result
    bool convertedAsLe;

    // Raw data (first byte only)
    QString binary;
    QString octal;

    // Text
    QString ascii; // All data converted !
    QString utf8;
    QString utf16;

    // Standard integer types
    QString u8;
    QString i8;
    QString u16;
    QString i16;
    QString u24;
    QString i24;
    QString u32;
    QString i32;
    QString u64;
    QString i64;
    QString u128;
    QString i128;

    // Standard float types
    QString f16;
    QString f16b;
    QString f32;
    QString f64;
    QString f128;

    // Others data types
    QString ts32;
    QString ts64;
};

} // namespace EtherBench::Services