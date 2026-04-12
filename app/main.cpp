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
#include <QFontDatabase>
#include <QIcon>

// ----------------------------------------------------------------------
// PROTOTYPES
// ----------------------------------------------------------------------
void apply_theme(QApplication &app, const QString &themePath);
void applyDarkPalette(QApplication &app);
void load_fonts();
void set_icon(QApplication &app, const QString &icon);

// ----------------------------------------------------------------------
// MAIN
// ----------------------------------------------------------------------
int main(int argc, char *argv[]) {

    // Create the app
    QApplication app(argc, argv);

    // Configure style
    app.setStyle("Fusion");
    apply_theme(app, ":/styles/dark.qss");
    applyDarkPalette(app);
    load_fonts();
    set_icon(app, ":/icons/app/etherbench.ico");

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

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(file.readAll());

        QMap<QString, QString> variables;
        variables["@accent"] = "#2a82da";
        variables["@accent_light"] = "#64abf1";
        variables["@bg_dark"] = "#1e1e1e";
        variables["@bg_med"] = "#2d2d2d";
        variables["@bg_light"] = "#3d3d3d";
        variables["@text"] = "#ffffff";
        variables["@text_dim"] = "#aaaaaa";
        variables["@border"] = "#0e4a87";

        for (auto it = variables.begin(); it != variables.end(); ++it) {
            styleSheet.replace(it.key(), it.value());
        }
        app.setStyleSheet(styleSheet);
        file.close();

    } else {
        qWarning() << "Unable to load the requested stylesheet : " << themePath;
    }
}

void applyDarkPalette(QApplication &app) {
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(30, 30, 30));
    darkPalette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(45, 45, 45));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    app.setPalette(darkPalette);
}

void load_fonts() {
    // Cinzel
    QFontDatabase::addApplicationFont(":/fonts/cinzel/static/Cinzel-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/cinzel/static/Cinzel-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/cinzel/static/Cinzel-ExtraBold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/cinzel/static/Cinzel-Medium.ttf");
    QFontDatabase::addApplicationFont(":/fonts/cinzel/static/Cinzel-SemiBold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/cinzel/Cinzel-VariableFont_wght.ttf");

    // Fira Code
    QFontDatabase::addApplicationFont(":/fonts/firacode/static/FiraCode-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/firacode/static/FiraCode-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/firacode/static/FiraCode-Light.ttf");
    QFontDatabase::addApplicationFont(":/fonts/firacode/static/Cinzel-Medium.ttf");
    QFontDatabase::addApplicationFont(":/fonts/firacode/static/Cinzel-SemiBold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/firacode/FiraCode-VariableFont_wght.ttf");
}

void set_icon(QApplication &app, const QString &icon) {
    QIcon appIcon(icon);
    app.setWindowIcon(appIcon);
}