#include "window.hpp"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EtherBench::UI::MainWindow win;
    win.show();

    return app.exec();
}