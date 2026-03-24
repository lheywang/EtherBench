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

class DebuggerModel : public QAbstractTableModel {
    Q_OBJECT

  public:
    DebuggerModel(QObject *parent = nullptr);
    ~DebuggerModel();

  public:
    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] int
    columnCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] QVariant
    data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  public slots:
    void appendPayload(const SpyPacket &packet);

  private:
    std::deque<SpyPacket> m_packets;
};