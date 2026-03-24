/**
 * @file    DebuggerField.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-24
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once
// =============================================================
// INCLUDES
// =============================================================
#include <QByteArray>
#include <QString>
#include <cstddef>
#include <cstdint>
#include <vector>

// =============================================================
// STRUCTS
// =============================================================
struct ProtocolField {
    QString name;
    size_t byteOffset;
    size_t byteLength;
    QString type;
    QString endianess;
    QString displayFormat;
};

struct DecoderField {
    QString name;
    QString value;
};
