/**
 * @file    memoryFile.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement the MemoryFile class
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
#include <models/memoryBuffer/memoryFile.hpp>

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
MemoryFile::MemoryFile(QObject *parent) : MemoryBuffer(parent) {}
MemoryFile::~MemoryFile() {}

/*
 * Overrides
 */
std::vector<uint8_t> MemoryFile::get(uint64_t offset, uint64_t size) {
    return std::vector<uint8_t>(0);
}
bool MemoryFile::append(std::vector<uint8_t> &data) { return true; }
bool MemoryFile::set(uint64_t offset, std::vector<uint8_t> &data) { return true; }
uint64_t MemoryFile::size() { return 0; }
uint8_t MemoryFile::at(uint64_t offset) const { return 0; }

} // namespace EtherBench::Models