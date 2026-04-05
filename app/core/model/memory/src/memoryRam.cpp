/**
 * @file    memoryRam.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement the MemoryRam class.
 * @version 0.1
 * @date    2026-04-05
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Header
#include <models/memoryRam.hpp>

// Local libraries
#include <models/memoryBuffer/memoryBuffer.hpp>

// Qt
#include <QObject>
#include <QString>

// STD
#include <array>
#include <vector>

// =============================================================
// NAMESPACE
// =============================================================
namespace EtherBench::Models {

// =============================================================
// CLASS
// =============================================================
MemoryRam::MemoryRam(QObject *parent) : MemoryBuffer(parent) {}
MemoryRam::~MemoryRam() {}

/*
 * Overrides
 */
std::vector<uint8_t> MemoryRam::get(uint64_t offset, uint64_t size) {
    return std::vector<uint8_t>(0);
}
bool MemoryRam::append(std::vector<uint8_t> &data) { return true; }
bool MemoryRam::set(uint64_t offset, std::vector<uint8_t> &data) { return true; }
uint64_t MemoryRam::size() { return 0; }
uint8_t MemoryRam::at(uint64_t offset) const { return 0; }

} // namespace EtherBench::Models