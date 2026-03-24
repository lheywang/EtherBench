/**
 * @file    main.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Base file that launch the GUI app.
 * @version 0.1
 * @date    2026-03-24
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Local libraries
#include "Core/AppCore.hpp"

// QT
#include <QGuiApplication>
#include <QQmlApplicationEngine>

// =============================================================
// ENTRY POINT
// =============================================================
int main(int argc, char *argv[]) {

    // Create the GUI applications
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Create the core controller
    AppCore appCore;

    // Register classes
    qmlRegisterSingletonInstance("EtherBench.Backend", 1, 0, "SystemCore", &appCore);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("App", "Main");

    // Start the app
    return app.exec();
}