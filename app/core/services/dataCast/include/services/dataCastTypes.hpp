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
#include <QStringList>

// =============================================================
// STRUCTS
// =============================================================
namespace EtherBench::Services {

struct dataCastResult {

    // Little endian result
    bool convertedAsLe;

    // Raw data (first byte only)
    QStringList binary;
    QStringList octal;

    // Text
    QStringList ascii; // All data converted !
    QStringList utf8;
    QStringList utf16;

    // Standard integer types
    QStringList u8;
    QStringList i8;
    QStringList u16;
    QStringList i16;
    QStringList u24;
    QStringList i24;
    QStringList u32;
    QStringList i32;
    QStringList u64;
    QStringList i64;
    QStringList u128;
    QStringList i128;

    // Standard float types
    // QStringList f16;
    // QStringList f16b;
    QStringList f32;
    QStringList f64;
    // QStringList f128;

    // Others data types
    QStringList ts32;
    QStringList ts64;
};

} // namespace EtherBench::Services