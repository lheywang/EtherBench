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
#include <models/memoryPool.hpp>

// Qt
#include <QObject>
#include <QtTest>

// =============================================================
// CLASS
// =============================================================

class MemoryPoolTest : public QObject {
    Q_OBJECT

    /*
     *QStringList defaults = {
        "Classic buffer",
        "Classic buffer",
        "Classic buffer",
        "Classic buffer",
        "Circular buffer",
        "Circular buffer",
        "File buffer",
        "File buffer"};
     */

  private slots:

    void testBasicInit() {
        auto &pool = EtherBench::Models::MemoryPool::instance();
        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT1),
            EtherBench::Models::BufferType::RAM);
        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT2),
            EtherBench::Models::BufferType::RAM);
        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT3),
            EtherBench::Models::BufferType::RAM);
        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT4),
            EtherBench::Models::BufferType::RAM);
        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT5),
            EtherBench::Models::BufferType::CIRCULAR);
        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT6),
            EtherBench::Models::BufferType::CIRCULAR);
        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT7),
            EtherBench::Models::BufferType::FILE);
        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT8),
            EtherBench::Models::BufferType::FILE);
    }

    void testBufferGet() {
        auto &pool = EtherBench::Models::MemoryPool::instance();
        auto flags = static_cast<EtherBench::Models::BufferIO>(
            EtherBench::Models::BufferIO::WRITE | EtherBench::Models::BufferIO::WRITE);

        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT1, EtherBench::Models::BufferType::RAM, flags) !=
            nullptr);
        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT2, EtherBench::Models::BufferType::RAM, flags) !=
            nullptr);
        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT3, EtherBench::Models::BufferType::RAM, flags) !=
            nullptr);
        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT4, EtherBench::Models::BufferType::RAM, flags) !=
            nullptr);
        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT5,
                EtherBench::Models::BufferType::CIRCULAR,
                flags) != nullptr);
        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT6,
                EtherBench::Models::BufferType::CIRCULAR,
                flags) != nullptr);
        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT7, EtherBench::Models::BufferType::FILE, flags) !=
            nullptr);
        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT8, EtherBench::Models::BufferType::FILE, flags) !=
            nullptr);

        pool.freeBuffer(EtherBench::Models::SLOT1);
        pool.freeBuffer(EtherBench::Models::SLOT2);
        pool.freeBuffer(EtherBench::Models::SLOT3);
        pool.freeBuffer(EtherBench::Models::SLOT4);
        pool.freeBuffer(EtherBench::Models::SLOT5);
        pool.freeBuffer(EtherBench::Models::SLOT6);
        pool.freeBuffer(EtherBench::Models::SLOT7);
        pool.freeBuffer(EtherBench::Models::SLOT8);
    }

    void testBufferReAlloc() {

        auto &pool = EtherBench::Models::MemoryPool::instance();
        auto flags = static_cast<EtherBench::Models::BufferIO>(
            EtherBench::Models::BufferIO::WRITE | EtherBench::Models::BufferIO::WRITE);

        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT1, EtherBench::Models::BufferType::RAM, flags) !=
            nullptr);

        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT1, EtherBench::Models::BufferType::RAM, flags) ==
            nullptr);

        pool.freeBuffer(EtherBench::Models::SLOT1);

        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT1, EtherBench::Models::BufferType::RAM, flags) !=
            nullptr);

        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT1, EtherBench::Models::BufferType::RAM, flags) ==
            nullptr);

        pool.freeBuffer(EtherBench::Models::SLOT1);
    }

    void testChangeBufferType() {

        auto &pool = EtherBench::Models::MemoryPool::instance();
        auto flags = static_cast<EtherBench::Models::BufferIO>(
            EtherBench::Models::BufferIO::WRITE | EtherBench::Models::BufferIO::WRITE);

        /*
         * First : test changes
         */
        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT1),
            EtherBench::Models::BufferType::RAM);

        pool.changeBufferType(
            EtherBench::Models::SLOT1, EtherBench::Models::BufferType::CIRCULAR);

        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT1),
            EtherBench::Models::BufferType::CIRCULAR);

        pool.changeBufferType(
            EtherBench::Models::SLOT1, EtherBench::Models::BufferType::RAM);

        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT1),
            EtherBench::Models::BufferType::RAM);

        /*
         * Second : test changes locks
         */
        QVERIFY(
            pool.getBuffer(
                EtherBench::Models::SLOT1, EtherBench::Models::BufferType::RAM, flags) !=
            nullptr);

        pool.changeBufferType(
            EtherBench::Models::SLOT1, EtherBench::Models::BufferType::CIRCULAR);

        QCOMPARE(
            pool.getBufferType(EtherBench::Models::SLOT1),
            EtherBench::Models::BufferType::RAM); // Wasn't changed !

        QCOMPARE(pool.getBufferIO(EtherBench::Models::SLOT1), flags);
    }
};

QTEST_MAIN(MemoryPoolTest)
#include "memoryPoolTest.moc"