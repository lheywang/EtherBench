/**
 * @file    lan.hpp
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
#include "DecoderModel/ProtocolsStructs.hpp"
#include <QByteArray>
#include <qobject.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================

class Lan : public QObject {
    Q_OBJECT
    QML_SINGLETON

    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectionChanged);
    Q_PROPERTY(QByteArray getData READ getData NOTIFY dataReady);

  public:
    explicit Lan(QObject *parent = nullptr);
    ~Lan();

  public:
    [[nodiscard]] bool isConnected() const;
    [[nodiscard]] QByteArray getData() const;

    Q_INVOKABLE void connectDevice();
    Q_INVOKABLE void disconnectDevice();

  signals:
    void connectionChanged();
    void dataReady(const SpyPacket &packet);

  private:
    bool m_isConnected;
    QByteArray m_getData;
};