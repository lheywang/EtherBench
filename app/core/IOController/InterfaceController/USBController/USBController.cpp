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
#include "DebuggerModel/DecoderModel/ProtocolsStructs.hpp"
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

    if (!this->m_mockTimer) {
        this->m_mockTimer = new QTimer(this);
        connect(
            this->m_mockTimer, &QTimer::timeout, this, &USBController::generateFakeData);
    }
    this->m_mockTimer->start(500);
    emit connectionChanged();
    return;
}

void USBController::disconnectDevice() {
    qInfo("[USBController] Disconnecting from device");
    return;
}

void USBController::generateFakeData() {
    SpyPacket packet;

    packet.timestamp = 1000000 + (this->m_mockCounter * 50000);
    packet.busId = (this->m_mockCounter % 2 == 0) ? 0x01 : 0x02;
    packet.isTx = (this->m_mockCounter % 3 == 0);
    packet.payload = QByteArray("\xDE\xAD\xBE\xEF");

    this->m_mockCounter += 1;

    emit this->dataReady(packet);
    return;
}