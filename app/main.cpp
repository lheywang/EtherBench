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

    qInfo("[Main] STEP 2 : Launching QML render engine.");
    QQmlApplicationEngine engine;

    qInfo("[Main] STEP 3 : Loading Main.qml");
    engine.loadFromModule("App", "Main");
    if (engine.rootObjects().isEmpty()) {
        qCritical() << "[Main] Failed to launch the GUI.";
        qCritical() << "[Main] Check the logs.";
        return -1;
    }

    // Start the app
    qInfo("[Main] STEP 4 : Launching the event loop ...");
    return app.exec();
}