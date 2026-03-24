/**
 * @file    DecoderModel.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-24
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDE
// =============================================================
// Header
#include "DecoderModel.hpp"

// Libs
#include "ProtocolsStructs.hpp"
#include <QObject>
#include <QtQml/qqml.h>
#include <qcontainerfwd.h>
#include <qobject.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================
DecoderModel::DecoderModel(QObject *parent) : QObject(parent) {

    // Just a temp value
    this->m_decodedBus = "";
    this->m_decodedPayload = "";
    this->m_decodedTimestamp = "";

    return;
}
DecoderModel::~DecoderModel() {};

QString DecoderModel::getDecodedTimestamp() const { return this->m_decodedTimestamp; }
QString DecoderModel::getDecodedBus() const { return this->m_decodedBus; }
QString DecoderModel::getDecodedPayload() const { return this->m_decodedPayload; }

void DecoderModel::decodeFrameAt(int rowIndex) {
    qInfo("[DecoderModel] Finished decoding frame %d", rowIndex);
    emit decodingComplete();
    return;
}