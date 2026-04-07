/**
 * @file    memoryPool.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Hold the memory pool class, and handle the standard IO over it.
 * @version 0.1
 * @date    2026-04-06
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// =============================================================
// INCLUDES
// =============================================================
// Local libraries
#include <models/memoryBuffer/memoryBuffer.hpp>
#include <models/memoryBuffer/memoryCircular.hpp>
#include <models/memoryBuffer/memoryFile.hpp>
#include <models/memoryBuffer/memoryRam.hpp>

// Qt
#include <QObject>
#include <QString>

// STD
#include <array>

namespace EtherBench::Models {

// =============================================================
// ENUMS
// =============================================================
// Define the different types
enum BufferType { NONE = 0, FILE, RAM, CIRCULAR };
enum BufferIO { READ = 1, WRITE };
enum BufferSlot { SLOT1, SLOT2, SLOT3, SLOT4, SLOT5, SLOT6, SLOT7, SLOT8, SLOT_COUNT };

// =============================================================
// CONSTEXPR
// =============================================================

// =============================================================
// CLASS
// =============================================================
class MemoryPool : public QObject {

  public:
    /*
     * As this class is a singleton, we'll just expose the instance
     */

    /**
     * @brief Return the instance of the Memory Pool that was created.
     *
     * @return MemoryPool&
     */
    static MemoryPool &instance();

    /*
     * Fetching and freeing the buffers.
     */
    /**
     * @brief Return an handle to a buffer, if :
     *      - The type is the correct one.
     *      - The buffer is available (only affect writes).
     *
     * @param bufferId The requested slot.
     * @param type The requested type.
     * @param IO The requested IO direction.
     * @return MemoryBuffer (may be nullptr !)
     */
    MemoryBuffer *getBuffer(BufferSlot bufferId, BufferType type, BufferIO IO);

    /**
     * @brief Mark the buffer as out of usage, and free for any usage. This actually does
     * not clear it. It just mark it as free for other to perform write operations on it.
     *
     * @param buffer A pointer to the current buffer.
     */
    void freeBuffer(BufferSlot bufferId);

    /**
     * @brief Change the type of a buffer. A call to the destructor is done, hence some
     * data may be lost in the operation.
     *
     * @warning This operation WILL fail if the buffer is currently openned in writting.
     *
     * @param bufferId The requested buffer slot to be changed.
     * @param requested_type The requested type.
     */
    void changeBufferType(BufferSlot bufferId, BufferType requested_type);

  private:
    /*
     * Private constructors and destructors
     */
    MemoryPool(QObject *parent = nullptr);
    ~MemoryPool();

    /*
     * Variables
     */
    std::array<MemoryBuffer *, SLOT_COUNT> m_slots;
    bool m_status[SLOT_COUNT];      // To keep track of which slot was given or not.
    BufferIO m_IO[SLOT_COUNT];      // To keep track of the currently used direction.
    BufferType m_types[SLOT_COUNT]; // To keep track of the current types.

    /*
     * Functions
     */
    /**
     * @brief Initialize the buffer, dependeding on the parameters.
     *
     */
    void initBuffers();

    void initBuffer(BufferSlot bufferId, BufferType type);

    /*
     * Mutexes
     */
    mutable QReadWriteLock m_lock{QReadWriteLock::Recursive};
};

} // namespace EtherBench::Models