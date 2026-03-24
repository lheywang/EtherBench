/**
 * @file    USBController.hpp
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
#include "DebuggerModel/DecoderModel/ProtocolsStructs.hpp"
#include <QByteArray>
#include <QObject>
#include <QTimer>
#include <qobject.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================

class USBController : public QObject {
    Q_OBJECT
    QML_SINGLETON

    Q_PROPERTY(bool isConnected READ isConnected NOTIFY connectionChanged);
    Q_PROPERTY(QByteArray getData READ getData NOTIFY dataReady);

  public:
    explicit USBController(QObject *parent = nullptr);
    ~USBController();

  public:
    [[nodiscard]] bool isConnected() const;
    [[nodiscard]] QByteArray getData() const;

    Q_INVOKABLE void connectDevice();
    Q_INVOKABLE void disconnectDevice();

  signals:
    void connectionChanged();
    void dataReady(const SpyPacket &packet);

  private slots:
    void generateFakeData();

  private:
    bool m_isConnected;
    QByteArray m_getData;

    QTimer *m_mockTimer{nullptr};
    uint64_t m_mockCounter{0};
};