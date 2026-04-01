/**
 * @file    main.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Main file, charged to launch the graphical interface.
 * @version 0.1
 * @date    2026-04-01
 *
 * @copyright Copyright (c) 2026
 *
 */

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
// Local libraries
#include "window.hpp"

// QT
#include <QApplication>

// ----------------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------------
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EtherBench::UI::MainWindow win;
    win.show();

    return app.exec();
}