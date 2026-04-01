/**
 * @file    EthernetController.cpp
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
#include "EthernetController.hpp"

// Libs
#include "DecoderModel/ProtocolsStructs.hpp"
#include <QByteArray>
#include <QObject>
#include <qobject.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================

EthernetController::EthernetController(QObject *parent) : QObject(parent) {
    qInfo("[EthernetController] Created the class instance");
    return;
}

EthernetController::~EthernetController() {
    qInfo("[EthernetController] Deleted the class instance");
    return;
}

bool EthernetController::isConnected() const { return m_isConnected; }

QByteArray EthernetController::getData() const {
    qInfo("[EthernetController] Fetched data buffer.");
    return this->m_getData;
}

void EthernetController::connectDevice() {
    qInfo("[EthernetController] Connecting to device");
    emit connectionChanged();
    return;
}

void EthernetController::disconnectDevice() {
    qInfo("[EthernetController] Disconnecting from device");
    return;
}