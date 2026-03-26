/**
 * @file    AppCore.cpp
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
#include "AppCore.hpp"

// Libraries
#include "DebuggerModel.hpp"
#include "DecoderModel/DecoderModel.hpp"
#include "IOController/InterfaceController/EthernetController/EthernetController.hpp"
#include "IOController/InterfaceController/USBController/USBController.hpp"
#include "SettingsModel.hpp"

#include <QMetaObject>
#include <QObject>
#include <QThread>
#include <memory>
#include <qobject.h>
#include <qthread.h>
#include <qtmetamacros.h>

// =============================================================
// CLASS
// =============================================================
AppCore::AppCore(QObject *parent)
    : QObject(parent), m_debuggerModel(std::make_unique<DebuggerModel>()),
      m_decoderModel(std::make_unique<DecoderModel>()) {

    // Register private structs
    qRegisterMetaType<SpyPacket>("SpyPacket");

    // Start execution engine
    this->setupHardwareThreads();
    qInfo("[AppCore] Created the IO threads.");
}

AppCore::~AppCore() {

    // Exit the threads
    this->m_usbThread.quit();
    this->m_ethThread.quit();

    // Wait for them to finish
    this->m_usbThread.wait();
    this->m_ethThread.wait();

    return;
}

DecoderModel *AppCore::getDecoder() const { return this->m_decoderModel.get(); }
DebuggerModel *AppCore::getDebuggerModel() const { return this->m_debuggerModel.get(); }
ConfigModel *AppCore::getSettingsModel() const { return this->m_settingModel.get(); }

void AppCore::setupHardwareThreads() {

    // Create the workers
    this->m_usbWorker = new USBController();
    this->m_ethWorker = new EthernetController();

    // Move them to their own threads
    this->m_usbWorker->moveToThread(&this->m_usbThread);
    this->m_ethWorker->moveToThread(&this->m_ethThread);

    // Ensure theses threads will free their memory by the end of
    // their execution.
    connect(
        &this->m_usbThread, &QThread::finished, this->m_usbWorker, &QObject::deleteLater);
    connect(
        &this->m_ethThread, &QThread::finished, this->m_ethWorker, &QObject::deleteLater);

    // Add the data pipes
    connect(
        this->m_usbWorker,
        &USBController::dataReady,
        m_debuggerModel.get(),
        &DebuggerModel::appendPayload);

    connect(
        this->m_ethWorker,
        &EthernetController::dataReady,
        m_debuggerModel.get(),
        &DebuggerModel::appendPayload);

    // Start the threads
    this->m_usbThread.start();
    this->m_ethThread.start();

    // Launch the connections
    QMetaObject::invokeMethod(this->m_usbWorker, "connectDevice", Qt::QueuedConnection);
    QMetaObject::invokeMethod(this->m_ethWorker, "connectDevice", Qt::QueuedConnection);

    return;
}
