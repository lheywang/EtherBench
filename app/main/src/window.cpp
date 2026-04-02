/**
 * @file    window.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Main implementation of the Window. Does generate the menubar and the basic
 *          stack layout.
 * @version 0.1
 * @date    2026-04-02
 *
 * @copyright Copyright (c) 2026
 *
 */

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
// Header
#include "window.hpp"
#include "views/sequenceView.hpp"

// Local Libraries
#include <views/debuggerView.hpp>
#include <views/helpView.hpp>
#include <views/homeView.hpp>
#include <views/ioView.hpp>
#include <views/memoryView.hpp>
#include <views/programmerView.hpp>
#include <views/settingsView.hpp>

// QT
#include <QActionGroup>
#include <QMenuBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <qaction.h>
#include <qapplication.h>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qstackedwidget.h>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------
namespace EtherBench::UI {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    /*
     * First, configure the global UI :
     */
    setupUI();
    setupMenuBar();
    setupSideBar();

    /*
     * Ensure objects are correctly linked to their models :
     */
    makeConnections();
}

void MainWindow::setupUI() {

    // Configure window parameters
    setWindowTitle("EtherBenchApp");
    resize(1280, 720);

    // Configure the children windows
    this->debuggerPage = new DebuggerView(this);
    this->helpPage = new HelpView(this);
    this->homePage = new HomeView(this);
    this->ioPage = new IOView(this);
    this->memoryPage = new MemoryView(this);
    this->programmerPage = new ProgrammerView(this);
    this->sequencePage = new SequenceView(this);
    this->settingsPage = new SettingsView(this);

    // Create the stacked layout
    this->m_viewStack = new QStackedWidget(this);

    m_viewStack->addWidget(homePage);
    m_viewStack->addWidget(debuggerPage);
    m_viewStack->addWidget(memoryPage);
    m_viewStack->addWidget(ioPage);
    m_viewStack->addWidget(programmerPage);
    m_viewStack->addWidget(sequencePage);
    m_viewStack->addWidget(settingsPage);
    m_viewStack->addWidget(helpPage);

    setCentralWidget(m_viewStack);
}

void MainWindow::setupMenuBar() {

    /*
     * Globals menus
     */
    fileMenu = menuBar()->addMenu("&Files");
    fileMenu->addAction("Exit", qApp, &QApplication::quit);

    viewMenu = menuBar()->addMenu("&View");
    viewMenu->addAction("Screenshot");
    viewMenu->addAction("Export to image");

    /*
     * Menus that aren't always showns :
     */
    // Memory
    memoryMenu = menuBar()->addMenu("&Memory");
    memoryMenu->menuAction()->setVisible(false);
    memoryMenu->addAction("Load binary");
    memoryMenu->addAction("Load executable");
    memoryMenu->addSeparator();
    memoryMenu->addAction("Export to file");
    memoryMenu->addSeparator();
    memoryMenu->addAction("Convert to executable");
    memoryMenu->addAction("Convert to binary");

    // Serial
    serialMenu = menuBar()->addMenu("&Serial");
    serialMenu->menuAction()->setVisible(false);
    serialMenu->addAction("Load serial session");
    serialMenu->addAction("Export serial session");
    serialMenu->addSeparator();
    serialMenu->addAction("Export session");

    // Build
    buildMenu = menuBar()->addMenu("&Build");
    buildMenu->menuAction()->setVisible(false);
    buildMenu->addAction("Open source");
    buildMenu->addAction("Save source");
    buildMenu->addSeparator();
    buildMenu->addAction("Compile");
    buildMenu->addAction("Decompile");
    buildMenu->addSeparator();
    buildMenu->addAction("Save to device");
    buildMenu->addAction("Load from device");

    // Debugger
    debuggerMenu = menuBar()->addMenu("&Debugger");
    debuggerMenu->menuAction()->setVisible(false);
    debuggerMenu->addAction("Save debugging session");
    debuggerMenu->addAction("Load debugging session");
}

void MainWindow::setupSideBar() {

    // Create the toolbar, and place it.
    auto *sidebar = new QToolBar("Naviguation", this);
    addToolBar(Qt::LeftToolBarArea, sidebar);

    // Configure the toolbar :
    sidebar->setMovable(false);
    sidebar->setIconSize(QSize(48, 48));
    sidebar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    sidebar->setContextMenuPolicy(Qt::PreventContextMenu);

    // Then, configure the actions :
    auto *navgroup = new QActionGroup(this);
    navgroup->setExclusive(true);

    // A small function to add a navaction without repeating too much the same coe ...
    auto addNavAction = [&](const QString &iconPath, const QString &text, int viewIndex) {
        QIcon icon(iconPath);
        if (icon.isNull()) {
            qWarning() << "ERREUR : Icône introuvable ->" << iconPath;
        }
        QAction *act = sidebar->addAction(icon, text);
        act->setCheckable(true);
        navgroup->addAction(act);
        connect(act, &QAction::triggered, this, [this, viewIndex]() {
            switchView(viewIndex);
        });
        return act;
    };

    actHome = addNavAction(":/icons/navbar/home.png", "Home", 0);
    actDebugger = addNavAction(":/icons/navbar/debugger.png", "Debugger", 1);
    actMemory = addNavAction(":/icons/navbar/memory.png", "Memory", 2);
    actIO = addNavAction(":/icons/navbar/io.png", "Serial IO", 3);
    actProgrammer = addNavAction(":/icons/navbar/programmer.png", "Programmer", 4);
    actSettings = addNavAction(":/icons/navbar/settings.png", "Settings", 5);
    actSettings = addNavAction(":/icons/navbar/sequences.png", "Sequences", 6);
    actHelp = addNavAction(":/icons/navbar/help.png", "Help", 7);

    // Set the default
    actHome->setChecked(true);
}

void MainWindow::makeConnections() {
    // connect(
    //     m_btn,
    //     &QPushButton::clicked,
    //     &m_counter,
    //     &EtherBench::Core::CounterManager::increment);

    // connect(
    //     &m_counter,
    //     &EtherBench::Core::CounterManager::countChanged,
    //     this,
    //     [this](int val) { m_label->setText(QString("Compteur : %1").arg(val)); });
}

/*
 * Naviguation functions
 */

void MainWindow::switchView(int index) {

    // Update the index
    this->m_viewStack->setCurrentIndex(index);

    // We also need to update the menu bar here

    // We can also configure the Window Title (and, perhaps, icon ? )
}

} // namespace EtherBench::UI