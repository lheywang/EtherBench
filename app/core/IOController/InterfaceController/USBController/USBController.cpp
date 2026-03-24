/**
 * @file    USBController.cpp
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
#include "USBController.hpp"

// Libs
#include <QByteArray>
#include <QObject>
#include <qobject.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================

USBController::USBController(QObject *parent) : QObject(parent) {
    qInfo("[USBController] Created the class instance");
    return;
}

USBController::~USBController() {
    qInfo("[USBController] Deleted the class instance");
    return;
}

bool USBController::isConnected() const { return this->m_isConnected; }

QByteArray USBController::getData() const {
    qInfo("[USBController] Fetched data buffer.");
    return this->m_getData;
}

void USBController::connectDevice() {
    qInfo("[USBController] Connecting to device");
    emit connectionChanged();
    return;
}

void USBController::disconnectDevice() {
    qInfo("[USBController] Disconnecting from device");
    return;
}