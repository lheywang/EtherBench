/**
 * @file    DebuggerModel.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-24
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// =============================================================
// INCLUDES
// =============================================================
#include "DebuggerField.hpp"

#include <QObject>
#include <QtQml/qqml.h>
#include <memory>
#include <qobject.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================

class DebuggerModel : public QObject {
    Q_OBJECT

  public:
    DebuggerModel(QObject *parent = nullptr);
    ~DebuggerModel();

  signals:

  public:
    void get();
    void appendPayload();

  private:
};