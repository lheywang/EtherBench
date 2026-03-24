/**
 * @file    DebuggerModel.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-24
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Header
#include "DebuggerModel.hpp"

// Libs
#include <QObject>
#include <QtQml/qqml.h>
#include <qobject.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================

DebuggerModel::DebuggerModel(QObject *parent)
    : QObject(parent) {

      };

DebuggerModel::~DebuggerModel() {}

void DebuggerModel::get() {
    qInfo("[DebuggerModel] Returned ourself !");
    return;
}

void DebuggerModel::appendPayload() {
    qInfo("[DebuggerMode] Added payload to the current FIFO");
    return;
};
