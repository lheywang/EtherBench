/**
 * @file    memoryTest2.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Handle global memory tests
 * @version 0.1
 * @date    2026-04-06
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Local libraries
#include <models/memoryBuffer/memoryRam.hpp>

// Qt
#include <QObject>
#include <QtTest>

// =============================================================
// CLASS
// =============================================================

class MemoryTest2 : public QObject {
    Q_OBJECT

  private slots:

    void testWriteRead() {
        EtherBench::Models::MemoryRam mem;
        std::vector<uint8_t> data = {0xDE, 0xAD, 0xBE, 0xEF};
        mem.set(0, data);

        QCOMPARE(mem.size(), (uint64_t)4);
        QCOMPARE(mem.at(0), 0xDE);
        QCOMPARE(mem.get(0, 4), data);
    }

    void testPageBoundary() {
        EtherBench::Models::MemoryRam mem;
        std::vector<uint8_t> data(10, 0xFF);
        uint64_t offset = EtherBench::Models::ALLOC_SIZE - 5;
        mem.set(offset, data);

        QCOMPARE(mem.at(offset), 0xFF);
        QCOMPARE(mem.at(offset + 9), 0xFF);
        QCOMPARE(mem.size(), offset + 10);
    }

    void testPageWrite() {
        EtherBench::Models::MemoryRam mem;
        std::vector<uint8_t> data(EtherBench::Models::ALLOC_SIZE, 0xFF);
        uint64_t offset = 0;
        mem.set(offset, data);

        QCOMPARE(mem.at(offset), 0xFF);
        QCOMPARE(mem.at(offset + data.size() - 1), 0xFF);
        QCOMPARE(mem.size(), data.size());
    }

    void testMultiplePageWrite() {
        uint64_t page_count = 256;
        EtherBench::Models::MemoryRam mem;
        std::vector<uint8_t> data(EtherBench::Models::ALLOC_SIZE * page_count, 0xFF);
        uint64_t offset = 0;
        mem.set(offset, data);

        QCOMPARE(mem.at(offset), 0xFF);
        QCOMPARE(mem.at(offset + data.size() - 1), 0xFF);
        QCOMPARE(mem.size(), data.size());
    }
};

QTEST_MAIN(MemoryTest2)
#include "memoryTest2.moc"