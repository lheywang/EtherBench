/**
 * @file    statusHub.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement inter process communication.
 * @version 0.1
 * @date    2026-04-08
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDE
// =============================================================
// Header
#include <models/statusHub.hpp>

// Qt
#include <QObject>
#include <QString>

// =============================================================
// INCLUDE
// =============================================================
namespace EtherBench::Models {

StatusHub &StatusHub::instance() {
    static StatusHub inst;
    return inst;
}

void StatusHub::info(const QString &msg) { emit messageRequested(msg, 3000); }
void StatusHub::error(const QString &msg) {
    emit messageRequested("[ERROR] " + msg, 5000);
}

} // namespace EtherBench::Models