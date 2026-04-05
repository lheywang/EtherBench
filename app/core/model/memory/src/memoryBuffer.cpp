/**
 * @file    memoryBuffer.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Implement the common MemoryBuffer features.
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
#include <models/memoryBuffer/memoryBuffer.hpp>

// Qt
#include <QObject>
#include <QString>

// STD
#include <array>
#include <vector>

// =============================================================
// CLASS
// =============================================================
namespace EtherBench::Models {

MemoryBuffer::MemoryBuffer(QObject *parent) : QObject(parent) {}

bool MemoryBuffer::erase(uint64_t offset, uint64_t size) { return true; }

void MemoryBuffer::loadFromFile(QString path) {}

void MemoryBuffer::writeToFile(QString path) {}

} // namespace EtherBench::Models
