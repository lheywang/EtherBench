/**
 * @file    memoryPool.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Hold the memory down, and coordinates IO over it.
 * @version 0.1
 * @date    2026-04-06
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Header
#include <models/memoryPool.hpp>

// Local libraries
#include <models/memoryBuffer/memoryBuffer.hpp>
#include <models/memoryBuffer/memoryCircular.hpp>
#include <models/memoryBuffer/memoryFile.hpp>
#include <models/memoryBuffer/memoryRam.hpp>
#include <models/parameterRegistry.hpp>

// Qt
#include <QDebug>
#include <QObject>
#include <QReadLocker>
#include <QReadWriteLock>
#include <QString>
#include <QStringList>
#include <QWriteLocker>

// STD
#include <array>

namespace EtherBench::Models {

// =============================================================
// CONSTEXPR
// =============================================================

// =============================================================
// CLASS
// =============================================================

MemoryPool::MemoryPool(QObject *parent) : QObject(parent) { initBuffers(); }
MemoryPool::~MemoryPool() {

    // Delete all memories.
    for (auto &mem : m_slots) {
        delete mem;
    }
}

MemoryPool &MemoryPool::instance() {
    static MemoryPool inst;
    return inst;
}

MemoryBuffer *MemoryPool::getBuffer(BufferSlot bufferId, BufferType type, BufferIO IO) {

    // Block everyone from touching the buffer
    QWriteLocker locker(&m_lock);

    // First, checks things about the buffer types
    if (type != m_types[bufferId]) {
        return nullptr;
    }

    // Check that both the write bit it set, as well the current one.
    if ((IO & BufferIO::WRITE) != 0) {
        if ((m_IO[bufferId] & BufferIO::WRITE) != 0) {
            return nullptr;
        }
    }

    // Then, we can proceed to the write.
    int flag = static_cast<int>(m_IO[bufferId]);
    flag |= IO;
    m_IO[bufferId] = static_cast<BufferIO>(flag);

    m_status[bufferId] = true;

    // Return the pointer
    return m_slots[bufferId];
}

void MemoryPool::freeBuffer(BufferSlot bufferId) {

    // Block everyone from touching the buffer
    QWriteLocker locker(&m_lock);

    // Update settings
    m_status[bufferId] = false;
    m_IO[bufferId] = static_cast<BufferIO>(0);
}

void MemoryPool::changeBufferType(BufferSlot bufferId, BufferType requested_type) {

    // Block everyone from touching the buffer
    QWriteLocker locker(&m_lock);

    if (m_IO[bufferId] != static_cast<BufferIO>(0)) {
        return;
    }

    // Delete the previous instance, and create the newer one.
    delete m_slots[bufferId];
    initBuffer(bufferId, requested_type);
}

void MemoryPool::initBuffers() {

    // Block everyone from touching the buffer
    QWriteLocker locker(&m_lock);

    // Fetch the parameters instance
    auto &reg = EtherBench::Models::ParameterRegistry::instance();

    for (int id = SLOT1; id < SLOT_COUNT; id += 1) {
        // Fetch the buffer type
        auto type = reg.get("device/memory/slot" + QString::number(id + 1)).value;

        // Identify the type
        BufferType buf_type = BufferType::RAM;
        if (type == "Circular buffer") {
            buf_type = BufferType::CIRCULAR;
        } else if (type == "File buffer") {
            buf_type = BufferType::FILE;
        }

        // Call it's associated init.
        initBuffer(static_cast<BufferSlot>(id), buf_type);
    }
}

void MemoryPool::initBuffer(BufferSlot bufferId, BufferType type) {

    switch (type) {
    case BufferType::RAM:
        m_slots[bufferId] = new MemoryRam(this);
        break;
    case BufferType::CIRCULAR:
        m_slots[bufferId] = new MemoryCircular(this);
        break;
    case BufferType::FILE:
        m_slots[bufferId] = new MemoryFile(this);
        break;
    default:
        m_slots[bufferId] = nullptr;
        qCritical() << "Got a NONE memory type as init. Pointer will remain null.";
        break;
    }

    return;
}

} // namespace EtherBench::Models