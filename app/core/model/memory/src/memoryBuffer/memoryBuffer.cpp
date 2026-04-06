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
#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QString>

// STD
#include <array>
#include <qlogging.h>
#include <qstringview.h>
#include <vector>

// =============================================================
// CLASS
// =============================================================
namespace EtherBench::Models {

MemoryBuffer::MemoryBuffer(QObject *parent) : QObject(parent) {}

bool MemoryBuffer::erase(uint64_t offset, uint64_t size) {

    // An erase command is basically a write with 0x00...
    std::vector<uint8_t> buf(size, 0);
    return set(offset, buf);
}

void MemoryBuffer::loadFromFile(QString path) {

    // Open the file and read the bytestream
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        qWarning() << "Unable to open binary file (r):" << path;
        return;
    }

    uint64_t offset = 0;
    while (!file.atEnd()) {
        QByteArray chunk =
            file.read(1024 * 1024); // Read 1MB per 1MB. Fast enough, and will be
                                    // transparent on the host side.
        if (chunk.isEmpty())
            break;

        std::vector<uint8_t> vec(chunk.begin(), chunk.end());
        if (!set(offset, vec)) {
            qCritical()
                << "Could not write to buffer, most probably because we can't get "
                   "enough memory.";
        }
        offset += chunk.size();
    }
    file.close();
    return;
}

void MemoryBuffer::writeToFile(QString path) {

    // Open the file :
    QFile file(path);
    if (!file.open(QFile::WriteOnly)) {
        qWarning() << "Unable to open binary file (w) :" << path;
        return;
    }

    uint64_t total_size = size();
    uint64_t chunk_size = (1024 * 1024); // Same logic, we won't write a buffer of 1 GB at
                                         // once ! Just do it by chunks of 1 MB.
    uint64_t offset = 0;

    while (offset < total_size) {
        uint64_t remaining = total_size - offset;
        uint64_t to_write = std::min(remaining, chunk_size);

        std::vector<uint8_t> data = get(offset, to_write);
        file.write(reinterpret_cast<const char *>(data.data()), data.size());

        offset += to_write;
    }

    file.close();
}

} // namespace EtherBench::Models
