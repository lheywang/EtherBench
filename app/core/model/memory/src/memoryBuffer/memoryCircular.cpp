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
#include <models/parameterRegistry.hpp>

// Qt
#include <QDebug>
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
MemoryCircular::MemoryCircular(QObject *parent) : MemoryBuffer(parent) {

    // Get the max size for our ram
    auto &reg = EtherBench::Models::ParameterRegistry::instance();
    auto param = reg.get("device/memory/circ_size").value;

    // Between 1 (MB) and 512 (MB). Then, multiply that by 1 MB to fetch the right value.
    auto tmp = param.value<QString>().split(" ")[0].toInt();
    max_buffer_size = (1ULL << 20) * tmp;

    // Compute the max page count
    max_page_count = max_buffer_size / ALLOC_SIZE;
    buffer_size = 0;
    head_pos = 0;
    writes = 0;

    // Allocate the first page in memory
    allocatePage();
}

MemoryCircular::~MemoryCircular() {

    // Clear the memory
    for (auto &arr : buffer) {
        delete arr;
    }
}

/*
 * Overrides
 */
std::vector<uint8_t> MemoryCircular::get(uint64_t offset, uint64_t size) {

    // Ensure data won't changed until we finished.
    QReadLocker locker(&m_lock);

    // Allocate the future buffer
    std::vector<uint8_t> arr(size, 0);

    // Copy the required content into a linear buffer.
    uint64_t bytes_copied = 0;
    while (bytes_copied < size) {

        uint64_t current_pos = (offset + bytes_copied) % max_buffer_size;
        uint64_t page_id = current_pos / ALLOC_SIZE;
        uint64_t page_offset = current_pos % ALLOC_SIZE;

        uint64_t remaining_in_page = ALLOC_SIZE - page_offset;
        uint64_t remaining_to_copy = size - bytes_copied;
        uint64_t chunk_size = std::min(remaining_in_page, remaining_to_copy);

        if (page_id < buffer.size() && buffer[page_id]) {
            std::memcpy(
                arr.data() + bytes_copied,
                buffer[page_id]->data() + page_offset,
                chunk_size);
        }

        bytes_copied += chunk_size;
    }

    return arr;
}

bool MemoryCircular::append(std::vector<uint8_t> &data) {

    // This ensure the class will always overwrite the data, rather than just being stuck.
    bool success = set(writes, data);
    if (success) {
        writes += data.size();
        head_pos = (head_pos + data.size()) % max_buffer_size;
    }
    return success;
}

bool MemoryCircular::set(uint64_t offset, std::vector<uint8_t> &data) {

    // Block everyone from touching the buffer
    QWriteLocker locker(&m_lock);

    // Copy the required content into a linear buffer.
    uint64_t bytes_copied = 0;
    while (bytes_copied < data.size()) {

        uint64_t current_pos = (offset + bytes_copied) % max_buffer_size;
        uint64_t page_id = current_pos / ALLOC_SIZE;
        uint64_t page_offset = current_pos % ALLOC_SIZE;

        // Allocate the data until we have enough pages.
        // Even then the circular buffer is circular, we don't allocate the whole size on
        // start. This ensure
        while (page_id >= buffer.size()) {
            if (!allocatePage()) {
                return false;
            }
        }

        uint64_t remaining_in_page = ALLOC_SIZE - page_offset;
        uint64_t remaining_to_copy = data.size() - bytes_copied;
        uint64_t chunk_size = std::min(remaining_in_page, remaining_to_copy);

        // perform the write.
        if (page_id < buffer.size() && buffer[page_id]) {
            std::memcpy(
                buffer[page_id]->data() + page_offset,
                data.data() + bytes_copied,
                chunk_size);
        }

        bytes_copied += chunk_size;
    }

    buffer_size = std::min(max_buffer_size, std::max(buffer_size, offset + data.size()));
    return true;
}

uint64_t MemoryCircular::size() {

    // Just return the current size
    return buffer_size;
}

uint8_t MemoryCircular::at(uint64_t offset) const {

    // Ensure data won't changed until we finished.
    QReadLocker locker(&m_lock);

    // Get the access address
    uint64_t page_id = (offset % max_buffer_size) / ALLOC_SIZE;
    uint64_t page_offset = (offset % max_buffer_size) % ALLOC_SIZE;

    // Return the data
    if (page_id >= buffer.size())
        return 0;
    return buffer[page_id]->at(page_offset);
}

uint64_t MemoryCircular::head() {

    // Just return the current size
    return head_pos;
}

bool MemoryCircular::allocatePage() {

    if (buffer.size() < max_page_count) {
        auto arr = new std::array<uint8_t, ALLOC_SIZE>;

        // If not
        if (arr != nullptr) {
            buffer.push_back(arr);
            return true;
        } else {
            qCritical() << "[MemoryCircular] Could not allocate a memory page.";
            return false;
        }
    }
    return false; // Reached the maximal size
}

} // namespace EtherBench::Models