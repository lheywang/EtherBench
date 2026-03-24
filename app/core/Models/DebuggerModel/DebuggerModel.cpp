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
#include "DebuggerField.hpp"
#include "DecoderModel/ProtocolsStructs.hpp"

#include <QAbstractTableModel>
#include <QObject>
#include <QtQml/qqml.h>
#include <deque>
#include <qobject.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================

DebuggerModel::DebuggerModel(QObject *parent)
    : QAbstractTableModel(parent) {

      };

DebuggerModel::~DebuggerModel() {}

int DebuggerModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return static_cast<int>(this->m_packets.size());
}

int DebuggerModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return 4; // 0: Time, 1: Bus, 2: Dir, 3: Payload
}

QVariant DebuggerModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_packets.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        const SpyPacket &packet = m_packets[index.row()];

        switch (index.column()) {
        case 0:
            return QString::number(packet.timestamp);
        case 1:
            return packet.busId == 0x01 ? "I2C" : "CAN";
        case 2:
            return packet.isTx ? "TX" : "RX";
        case 3:
            return QString(packet.payload.toHex(' ').toUpper());
        default:
            return QVariant();
        }
    }
    return QVariant();
}

void DebuggerModel::appendPayload(const SpyPacket &packet) {
    qInfo("[DebuggerMode] Added payload to the current FIFO");

    const int newRow = static_cast<int>(this->m_packets.size());

    beginInsertRows(QModelIndex(), newRow, newRow);
    m_packets.push_back(packet);
    endInsertRows();

    return;
};
