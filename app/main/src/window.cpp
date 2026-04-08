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
#include "models/statusHub.hpp"
#include "views/sequenceView.hpp"

// Local Libraries
#include <qstatusbar.h>
#include <views/debuggerView.hpp>
#include <views/helpView.hpp>
#include <views/homeView.hpp>
#include <views/ioView.hpp>
#include <views/memoryView.hpp>
#include <views/muxerView.hpp>
#include <views/plotView.hpp>
#include <views/programmerView.hpp>
#include <views/settingsView.hpp>

// Models
#include <models/parameterRegistry.hpp>
#include <models/statusHub.hpp>

// QT
#include <QActionGroup>
#include <QCloseEvent>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------
namespace EtherBench::UI {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    /*
     * Load the settings
     */
    auto &reg = EtherBench::Models::ParameterRegistry::instance();
    reg.initParams();
    reg.loadFromFile("settings.ebs");

    /*
     * First, configure the global UI :
     */
    setupUI();
    setupMenuBar();
    setupSideBar();
    setupStatusBar();

    /*
     * Ensure objects are correctly linked to their models :
     */
    makeConnections();
}

void MainWindow::setupUI() {

    // Configure window parameters
    setWindowTitle("EtherBenchApp - Home");
    resize(1280, 720);
    this->setMinimumHeight(650);
    this->setMinimumWidth(700);

    // Configure the children windows
    this->pages[ViewType::Home] = new HomeView(this);
    this->pages[ViewType::Debugger] = new DebuggerView(this);
    this->pages[ViewType::Memory] = new MemoryView(this);
    this->pages[ViewType::Serial] = new IOView(this);
    this->pages[ViewType::Programmer] = new ProgrammerView(this);
    this->pages[ViewType::Sequences] = new SequenceView(this);
    this->pages[ViewType::Muxer] = new MuxerView(this);
    this->pages[ViewType::Settings] = new SettingsView(this);
    this->pages[ViewType::Help] = new HelpView(this);
    this->pages[ViewType::Plot] = new PlotView(this);

    // Create the stacked layout
    this->m_viewStack = new QStackedWidget(this);

    // Add all the windows
    for (int i = 0; i < static_cast<int>(ViewType::Count); i += 1) {
        ViewType type = static_cast<ViewType>(i);
        if (this->pages.contains(type)) {
            this->m_viewStack->addWidget(this->pages[type]);
        }
    }

    setCentralWidget(m_viewStack);

    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    centralWidget()->layout()->setSpacing(0);
}

void MainWindow::setupMenuBar() {

    m_menuBar = new QMenuBar();
    this->setMenuBar(m_menuBar);

    addMenuBarElements();
}

void MainWindow::addMenuBarElements() {

    /*
     * Globals menus
     */
    fileMenu = m_menuBar->addMenu("&Files");
    fileMenu->addAction("Exit", this, &MainWindow::exit);

    viewMenu = m_menuBar->addMenu("&View");
    viewMenu->addAction("Screenshot");
    viewMenu->addAction("Export to image");
}

void MainWindow::setupSideBar() {

    // Create the toolbar, and place it.
    auto *sidebar = new QToolBar("Naviguation", this);
    addToolBar(Qt::LeftToolBarArea, sidebar);

    // Configure the toolbar :
    sidebar->setMovable(false);
    sidebar->setIconSize(QSize(32, 32));
    sidebar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    sidebar->setContextMenuPolicy(Qt::PreventContextMenu);

    // Then, configure the actions :
    auto *navgroup = new QActionGroup(this);
    navgroup->setExclusive(true);

    // A small function to add a navaction without repeating too much the same code ...
    auto addNavAction = [&](const QString &iconPath, const QString &text, int viewIndex) {
        QIcon icon(iconPath);
        if (icon.isNull()) {
            qWarning() << "Failed to find icon : " << iconPath;
        }
        QAction *act = sidebar->addAction(icon, text);
        act->setCheckable(true);
        navgroup->addAction(act);
        connect(act, &QAction::triggered, this, [this, viewIndex]() {
            switchView(static_cast<ViewType>(viewIndex));
        });
        return act;
    };

    actHome = addNavAction(":/icons/navbar/home.png", "Home", 0);
    actDebugger = addNavAction(":/icons/navbar/debugger.png", "Debugger", 1);
    actPlotter = addNavAction(":/icons/navbar/plot.png", "Plots", 2);
    actIO = addNavAction(":/icons/navbar/io.png", "Serial IO", 3);
    actMemory = addNavAction(":/icons/navbar/memory.png", "Memory", 4);
    actProgrammer = addNavAction(":/icons/navbar/programmer.png", "Programmer", 5);
    actSequences = addNavAction(":/icons/navbar/sequences.png", "Sequences", 6);
    actMuxer = addNavAction(":/icons/navbar/routing.png", "IO Mux", 7);

    // Add a space, just to make things look a bit better.
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sidebar->addWidget(spacer);

    actSettings = addNavAction(":/icons/navbar/settings.png", "Settings", 8);
    actHelp = addNavAction(":/icons/navbar/help.png", "Help", 9);

    // Set the default
    actHome->setChecked(true);
}

void MainWindow::setupStatusBar() {

    setStatusBar(new QStatusBar(this));
    statusBar()->show();
    statusBar()->showMessage("Ready", 5000);
}

void MainWindow::makeConnections() {

    // Connecting the statusbar event
    connect(
        &Models::StatusHub::instance(),
        &Models::StatusHub::messageRequested,
        this->statusBar(),
        &QStatusBar::showMessage);
}

/*
 * Naviguation functions
 */

void MainWindow::switchView(ViewType type) {

    // Disable the previous page
    ViewType current = static_cast<ViewType>(this->m_viewStack->currentIndex());
    this->pages[current]->onDeactivated();

    // Update the view
    m_viewStack->setCurrentWidget(this->pages[type]);

    // Set the new config of the window
    setWindowTitle("EtherBench - " + this->pages[type]->viewTitle());
    this->pages[type]->onActivated();

    // Clear the current menubar
    m_menuBar->clear();

    // Add the "new" menubar
    addMenuBarElements();
    this->pages[type]->fillMenubar(this->m_menuBar);

    // Update the menubar
}

/*
 * Window management
 */

void MainWindow::closeEvent(QCloseEvent *event) {
    prepare_exit();
    event->accept();
}

void MainWindow::exit() {

    prepare_exit();
    QApplication::quit();
}

void MainWindow::prepare_exit() {
    // Save parameter registry
    auto &reg = EtherBench::Models::ParameterRegistry::instance();
    reg.writeToFile("settings.ebs");
    qInfo() << "Saved parameter registry to file.";
}

} // namespace EtherBench::UI