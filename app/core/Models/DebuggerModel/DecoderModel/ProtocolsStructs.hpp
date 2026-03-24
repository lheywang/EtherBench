/**
 * @file    ProtocolsStructs.hpp
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
#include <cstdint>

// =============================================================
// STRUCTS
// =============================================================
struct SpyPacket {
    uint64_t timestamp;
    uint8_t busId;
    bool isTx;
    QByteArray payload;
};
