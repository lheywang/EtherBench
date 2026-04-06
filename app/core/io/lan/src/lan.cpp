/**
 * @file    lan.cpp
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
#include "Lan.hpp"

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

Lan::Lan(QObject *parent) : QObject(parent) {
    qInfo("[Lan] Created the class instance");
    return;
}

Lan::~Lan() {
    qInfo("[Lan] Deleted the class instance");
    return;
}

bool Lan::isConnected() const { return m_isConnected; }

QByteArray Lan::getData() const {
    qInfo("[Lan] Fetched data buffer.");
    return this->m_getData;
}

void Lan::connectDevice() {
    qInfo("[Lan] Connecting to device");
    emit connectionChanged();
    return;
}

void Lan::disconnectDevice() {
    qInfo("[Lan] Disconnecting from device");
    return;
}