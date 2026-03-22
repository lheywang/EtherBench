#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "bridge/SystemController/SystemController.hpp"

int main(
    int argc,
    char *argv[]
) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    SystemController sysController;
    
    engine.rootContext()->setContextProperty("sysController", &sysController);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );

    engine.loadFromModule("App", "Main");

    return app.exec();
}