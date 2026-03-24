/**
 * @file    AppCore.hpp
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
#include "IOController/InterfaceController/EthernetController/EthernetController.hpp"
#include "IOController/InterfaceController/USBController/USBController.hpp"
#include "Models/DebuggerModel/DebuggerModel.hpp"
#include "Models/DebuggerModel/DecoderModel/DecoderModel.hpp"

#include <QObject>
#include <QThread>
#include <memory>
#include <qobject.h>
#include <qthread.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================
class AppCore : public QObject {
    Q_OBJECT
    QML_SINGLETON

    Q_PROPERTY(DecoderModel *decoder READ getDecoder CONSTANT)
    Q_PROPERTY(DebuggerModel *debuggerModel READ getDebuggerModel CONSTANT)

  public:
    /*
     * Constructors and Destructors
     */
    explicit AppCore(QObject *parent = nullptr);
    ~AppCore() override;

  public:
    [[nodiscard]] DecoderModel *getDecoder() const;
    [[nodiscard]] DebuggerModel *getDebuggerModel() const;

  private:
    /*
     * Threads definitions
     */
    QThread m_usbThread;
    QThread m_ethThread;

    /*
     * Workers definitions
     */
    EthernetController *m_ethWorker;
    USBController *m_usbWorker;

    /*
     * Models
     */
    std::unique_ptr<DebuggerModel> m_debuggerModel;
    std::unique_ptr<DecoderModel> m_decoderModel;

    /*
     * Functions
     */
    /**
     * @brief Start up the low level IO threads.
     */
    void setupHardwareThreads();

  private:
};