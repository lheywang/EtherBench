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

    const QUrl url(QStringLiteral("qrc:/qt/qml/App/qml/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );

    engine.load(url);

    return app.exec();
}