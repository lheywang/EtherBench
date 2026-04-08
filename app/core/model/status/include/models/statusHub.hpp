/**
 * @file    statusHub.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Handle the status communication between different processes.
 * @version 0.1
 * @date    2026-04-08
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// =============================================================
// INCLUDE
// =============================================================
// Qt
#include <QObject>
#include <QString>

namespace EtherBench::Models {

// =============================================================
// CLASS
// =============================================================

class StatusHub : public QObject {
    Q_OBJECT
  public:
    static StatusHub &instance();
    void info(const QString &msg);
    void error(const QString &msg);

  signals:
    void messageRequested(QString message, int timeout);

  private:
    StatusHub() = default;
};

} // namespace EtherBench::Models