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
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QReadLocker>
#include <QReadWriteLock>
#include <QString>
#include <QWriteLocker>

// STD
#include <array>
#include <string>
#include <vector>

// =============================================================
// NAMESPACE
// =============================================================
namespace EtherBench::Models {

// =============================================================
// CLASS
// =============================================================
MemoryFile::MemoryFile(QObject *parent) : MemoryFile("", parent) {};
MemoryFile::MemoryFile(QString filepath, QObject *parent) : MemoryBuffer(parent) {
    buffer = nullptr;
    buffer_size = 0;
    head = 0;

    // Load the file from there.
    if (filepath != "") {
        loadFromFile(filepath);
        QFileInfo info(filepath);
    }
}
MemoryFile::~MemoryFile() { unmap(); }

/*
 * Overrides
 */
std::vector<uint8_t> MemoryFile::get(uint64_t offset, uint64_t size) {

    // Ensure data won't changed until we finished.
    QReadLocker locker(&m_lock);

    // Create our response buffer
    std::vector<uint8_t> vec(size, 0x00);

    // Check if we're not out of bounds
    if ((!buffer) || ((offset + size) > head)) {
        return vec;
    }

    if (buffer) {
        memcpy(vec.data(), buffer + offset, size);
    }
    return vec;
}
bool MemoryFile::append(std::vector<uint8_t> &data) {

    // Just set at the end of the buffer.
    return set(head, data);
}

bool MemoryFile::set(uint64_t offset, std::vector<uint8_t> &data) {

    // Block everyone from touching the buffer
    QWriteLocker locker(&m_lock);

    // First, ensure our memory space is correctly configured.
    // if not, request the missing byte (round to 16 MB, because this operation is costly,
    // this, we won't map for 2 bytes...).
    uint64_t requested = offset + data.size();
    if (requested > buffer_size) {
        if (!resize(std::max((requested - buffer_size), (1ULL << 24)))) {
            return false;
        }
    }

    // Copy the data into the right place
    if (buffer) {
        memcpy(buffer + offset, data.data(), data.size());
        head = std::max(head, requested);
        return true;
    }
    return false;
}

uint64_t MemoryFile::size() { return head; }

uint8_t MemoryFile::at(uint64_t offset) const {

    // Ensure data won't changed until we finished.
    QReadLocker locker(&m_lock);

    if ((buffer) && (offset < head)) {
        return buffer[offset];
    }
    return 0;
}

void MemoryFile::loadFromFile(QString path) {

    // Block everyone from touching the buffer
    QWriteLocker locker(&m_lock);

    // Ensure the file isn't already openned (as this function won't close it afterward)
    if (buffer) {
        memfile.unmap(buffer);
    }

    // Clear buffer, just in case
    buffer = nullptr;
    buffer_size = 0;

    // Open the file
    memfile.setFileName(path);
    if (!memfile.open(QFile::ReadWrite)) {
        qCritical() << "[MemoryFile] Failed to open :" << path;
        return;
    }

    // Resize if needed, to 1 MB (default value)
    if (memfile.size() == 0) {
        head = 0;
        if (!memfile.resize(get_new_buffer_size(buffer_size)))
            return;
    } else {
        head = memfile.size();
    }
    buffer_size = memfile.size();

    // Mapping it (all)
    buffer = memfile.map(0, buffer_size);
    if (!buffer) {
        qCritical() << "[MemoryFile] Failed to map file to memory :"
                    << memfile.errorString();
        return;
    }

    filename = path;
    return;
}
void MemoryFile::writeToFile(QString path) {

    // Ensure data won't changed until we finished.
    QReadLocker locker(&m_lock);

    // Flush on disk
    unmap();

    // If it's not ourselve, just copy.
    if (path != filename) {
        QFile::copy(filename, path);
    }
}

bool MemoryFile::resize(uint64_t request) {

    // First, save settings and unmap
    uint64_t current_head = head;
    unmap();

    // Resize the file
    memfile.resize(get_new_buffer_size(buffer_size, request));

    // Reload it and restore
    loadFromFile(filename);
    head = current_head;

    return (buffer != nullptr);
}

bool MemoryFile::unmap() {
    // The write operation is much simpler, as all the heavy job is done by the OS, and
    // not us.
    if (buffer) {
        memfile.unmap(buffer);
        buffer = nullptr;
    }
    if (memfile.isOpen()) {
        memfile.close();
    }

    return true;
}

} // namespace EtherBench::Models