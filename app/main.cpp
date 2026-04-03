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
#include <QFile>

// ----------------------------------------------------------------------
// PROTOTYPES
// ----------------------------------------------------------------------
void apply_theme(QApplication &app, const QString &themePath);

// ----------------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------------
int main(int argc, char *argv[]) {

    // Create the app
    QApplication app(argc, argv);

    // Configure style
    app.setStyle("Fusion");
    apply_theme(app, ":/styles/dark.qss");

    // Launch the app
    EtherBench::UI::MainWindow win;
    win.show();

    return app.exec();
}

// ----------------------------------------------------------------------
// FUNCTIONS
// ----------------------------------------------------------------------
void apply_theme(QApplication &app, const QString &themePath) {

    // Open and load the file
    QFile file(themePath);

    if (file.open(QFile::ReadOnly |QFile::Text)) {

        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
        file.close();
    } else {
        qWarning() << "Unable to load the requested stylesheet : " << themePath;
    }
}