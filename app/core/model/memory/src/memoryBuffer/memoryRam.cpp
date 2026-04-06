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
#include <models/memoryBuffer/memoryRam.hpp>

// Local libraries
#include <models/memoryBuffer/memoryBuffer.hpp>

// Qt
#include <QDebug>
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
MemoryRam::MemoryRam(QObject *parent) : MemoryBuffer(parent) { allocatePage(); }
MemoryRam::~MemoryRam() {

    // Clear the memory
    for (auto &arr : buffer) {
        delete arr;
    }
}

/*
 * Overrides
 */
std::vector<uint8_t> MemoryRam::get(uint64_t offset, uint64_t size) {

    // Allocate the future buffer
    std::vector<uint8_t> arr(size, 0);

    // Copy the required content into a linear buffer.
    uint64_t bytes_copied = 0;
    while (bytes_copied < size) {

        uint64_t current_pos = offset + bytes_copied;
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

bool MemoryRam::append(std::vector<uint8_t> &data) {

    // We can just call set at the end of our file
    return set(buffer_size, data);
}

bool MemoryRam::set(uint64_t offset, std::vector<uint8_t> &data) {

    // Copy the required content into a linear buffer.
    uint64_t bytes_copied = 0;
    while (bytes_copied < data.size()) {

        uint64_t current_pos = offset + bytes_copied;
        uint64_t page_id = current_pos / ALLOC_SIZE;
        uint64_t page_offset = current_pos % ALLOC_SIZE;

        // Allocate the data until we have enough pages.
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

    buffer_size = std::max(buffer_size, offset + data.size());
    return true;
}

uint64_t MemoryRam::size() {

    // Just return the current size
    return buffer_size;
}

uint8_t MemoryRam::at(uint64_t offset) const {

    // Get the access address
    uint64_t page_id = offset / ALLOC_SIZE;
    uint64_t page_offset = offset % ALLOC_SIZE;

    // Return the data
    if (page_id >= buffer.size())
        return 0;
    return buffer[page_id]->at(page_offset);
}

bool MemoryRam::allocatePage() {
    // Add the first buffer
    auto arr = new std::array<uint8_t, ALLOC_SIZE>;

    // If not
    if (arr != nullptr) {
        buffer.push_back(arr);
        buffer_size = 0;
        return true;
    } else {
        qCritical() << "[MemoryRam] Could not allocate a memory page.";
        return false;
    }
}

} // namespace EtherBench::Models