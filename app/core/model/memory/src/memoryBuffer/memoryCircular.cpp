/**
 * @file    memoryCircular.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement the MemoryCircular class
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
#include <models/memoryBuffer/memoryCircular.hpp>

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
MemoryCircular::MemoryCircular(QObject *parent) : MemoryBuffer(parent) {}
MemoryCircular::~MemoryCircular() {}

/*
 * Overrides
 */
std::vector<uint8_t> MemoryCircular::get(uint64_t offset, uint64_t size) {
    return std::vector<uint8_t>(0);
}
bool MemoryCircular::append(std::vector<uint8_t> &data) { return true; }
bool MemoryCircular::set(uint64_t offset, std::vector<uint8_t> &data) { return true; }
uint64_t MemoryCircular::size() { return 0; }
uint8_t MemoryCircular::at(uint64_t offset) const { return 0; }

} // namespace EtherBench::Models