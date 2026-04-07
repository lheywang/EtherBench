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
#include <models/memoryBuffer/memoryFile.hpp>

// Qt
#include <QObject>
#include <QtTest>

// =============================================================
// CLASS
// =============================================================

class MemoryFileTest : public QObject {
    Q_OBJECT

  private slots:

    void testBasicMapping() {
        QString path = "test_mapping_file.bin";
        QFile::remove(path);

        {
            EtherBench::Models::MemoryFile mem(nullptr, path);
            std::vector<uint8_t> data = {0xAA, 0xBB, 0xCC, 0xDD};
            mem.set(0, data);

            QCOMPARE(mem.size(), (uint64_t)4);
            QCOMPARE(mem.at(0), 0xAA);
        }

        QVERIFY(QFile::exists(path));
        QFile::remove(path);
    }

    void testAutoResize() {
        QString path = "test_resize_file.bin";
        QFile::remove(path);

        EtherBench::Models::MemoryFile mem(nullptr, path);

        uint64_t farOffset = 20 * 1024 * 1024;
        std::vector<uint8_t> data = {0xFF};
        mem.set(farOffset, data);

        QCOMPARE(mem.size(), farOffset + 1);

        QFileInfo info(path);
        QVERIFY(info.size() >= (20 * 1024 * 1024));

        QFile::remove(path);
    }

    void testPersistence() {
        QString path = "test_persist_file.bin";
        QFile::remove(path);

        {
            EtherBench::Models::MemoryFile mem(nullptr, path);
            std::vector<uint8_t> data = {0x11, 0x22, 0x33, 0x44};
            mem.append(data);
        }

        {
            EtherBench::Models::MemoryFile memLoaded(nullptr, path);

            // 1 MB, as the file is loaded, we lost track of head.
            QCOMPARE(memLoaded.size(), (uint64_t)(1ULL << 20));
            QCOMPARE(memLoaded.at(0), 0x11);
            QCOMPARE(memLoaded.at(3), 0x44);
        }

        QFile::remove(path);
    }

    void testSaveAs() {
        QString original = "original_file.bin";
        QString backup = "backup_file.bin";
        QFile::remove(original);
        QFile::remove(backup);

        EtherBench::Models::MemoryFile mem(nullptr, original);
        std::vector<uint8_t> data = {0xDE, 0xAD, 0xBE, 0xEF};
        mem.append(data);
        mem.writeToFile(backup);

        QVERIFY(QFile::exists(backup));
        QFileInfo info(backup);

        // 1 MB, as the head is 4, yes, but, the file was mapped to 1 MB. So, we need to
        // account for that
        QCOMPARE(info.size(), (qint64)(1ULL << 20));
        QCOMPARE(mem.size(), (qint64)(4));

        QFile::remove(original);
        QFile::remove(backup);
    }
};

QTEST_MAIN(MemoryFileTest)
#include "memoryFileTest.moc"