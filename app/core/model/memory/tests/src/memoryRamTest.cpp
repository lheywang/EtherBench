/**
 * @file    memoryTest.cpp
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

class MemoryRamTest : public QObject {
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
        uint64_t page_count = 65536;
        EtherBench::Models::MemoryRam mem;
        std::vector<uint8_t> data(EtherBench::Models::ALLOC_SIZE * page_count, 0xFF);
        uint64_t offset = 0;
        mem.set(offset, data);

        QCOMPARE(mem.at(offset), 0xFF);
        QCOMPARE(mem.at(offset + data.size() - 1), 0xFF);
        QCOMPARE(mem.size(), data.size());
    }

    void testOutOfBoundValue() {
        EtherBench::Models::MemoryRam mem;

        QCOMPARE(mem.at(5000), 0x00);
    }

    void testAppendRead() {
        EtherBench::Models::MemoryRam mem;
        std::vector<uint8_t> data = {0xDE, 0xAD, 0xBE, 0xEF};
        mem.append(data);

        QCOMPARE(mem.size(), (uint64_t)4);
        QCOMPARE(mem.at(0), 0xDE);
        QCOMPARE(mem.get(0, 4), data);
    }

    void testFileRoundtrip() {
        EtherBench::Models::MemoryRam mem;
        QString testPath = "roundtrip_test_ram.bin";

        std::vector<uint8_t> originalData = {0x45, 0x74, 0x68, 0x65, 0x72};
        mem.append(originalData);

        mem.writeToFile(testPath);
        QVERIFY(QFile::exists(testPath));

        EtherBench::Models::MemoryRam memLoaded;
        memLoaded.loadFromFile(testPath);

        QCOMPARE(memLoaded.size(), (uint64_t)originalData.size());
        QCOMPARE(memLoaded.get(0, 5), originalData);

        QFile::remove(testPath);
    }

    void testLargeFileIO() {
        EtherBench::Models::MemoryRam mem;
        QString testPath = "large_io_test_ram.bin";

        uint64_t totalSize = (2.5 * 1024 * 1024);
        std::vector<uint8_t> largeData(totalSize, 0xAB);
        mem.set(0, largeData);

        mem.writeToFile(testPath);

        QFileInfo info(testPath);
        QCOMPARE((uint64_t)info.size(), totalSize);

        EtherBench::Models::MemoryRam memLoaded;
        memLoaded.loadFromFile(testPath);

        QCOMPARE(memLoaded.size(), totalSize);
        QCOMPARE(memLoaded.at(1024 * 1024 + 50), 0xAB);
        QCOMPARE(memLoaded.at(totalSize - 1), 0xAB);

        QFile::remove(testPath);
    }

    void testInvalidFile() {
        EtherBench::Models::MemoryRam mem;

        mem.loadFromFile("non_existent_file_ram.bin");
        QCOMPARE(mem.size(), (uint64_t)0);

        if (QSysInfo::productType() == "windows") {
            mem.writeToFile("Z:/unlikely/path/file_ram.bin");
        }
    }
};

QTEST_MAIN(MemoryRamTest)
#include "memoryRamTest.moc"