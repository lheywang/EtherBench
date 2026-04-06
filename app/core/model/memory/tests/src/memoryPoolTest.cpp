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

  private slots:
};

QTEST_MAIN(MemoryPoolTest)
#include "memoryPoolTest.moc"