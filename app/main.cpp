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
#include "DebuggerModel/DebuggerModel.hpp"

// QT
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// =============================================================
// ENTRY POINT
// =============================================================
int main(int argc, char *argv[]) {
    qputenv("QT_QUICK_CONTROLS_STYLE", "Material");

    // Create the GUI applications
    qInfo("[Main] STEP 1 : Initializing OS part.");
    QGuiApplication app(argc, argv);

    // Create the core controller
    qInfo("[Main] STEP 2 : Starting C++ Backend.");
    AppCore appCore;

    qInfo("[Main] STEP 3 : Launching QML render engine.");
    QQmlApplicationEngine engine;

    QObject::connect(
        &engine, &QQmlApplicationEngine::warnings, [](const QList<QQmlError> &warnings) {
            for (const auto &w : warnings) {
                qCritical() << "[MAIN : QML ERROR DETECTED] ->" << w.toString();
            }
        });
    engine.rootContext()->setContextProperty("SystemCore", &appCore);

    qmlRegisterSingletonInstance("EtherBench.Backend", 1, 0, "SystemCore", &appCore);
    qmlRegisterUncreatableType<DebuggerModel>(
        "EtherBench.Models",
        1,
        0,
        "DebuggerModel",
        "Models are handled by the SystemCore.");

    qInfo("[Main] STEP 4 : Loading Main.qml");
    engine.loadFromModule("App", "Main");

    // VÉRIFICATION FATALE
    if (engine.rootObjects().isEmpty()) {
        qCritical() << "[Main] Failed to launch the GUI.";
        qCritical() << "[Main] Check the logs.";
        return -1;
    }

    // Start the app
    qInfo("[Main] STEP 5 : Launching the event loop ...");
    return app.exec();
}