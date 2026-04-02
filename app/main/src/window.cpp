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

// Local Libraries
#include <qstackedwidget.h>
#include <views/debuggerView.hpp>
#include <views/helpView.hpp>
#include <views/homeView.hpp>
#include <views/ioView.hpp>
#include <views/memoryView.hpp>
#include <views/programmerView.hpp>
#include <views/settingsView.hpp>

// QT
#include <QVBoxLayout>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------
namespace EtherBench::UI {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    makeConnections();
}

void MainWindow::setupUI() {

    // Configure window parameters
    setWindowTitle("EtherBenchApp");
    resize(1280, 720);

    // Configure the children windows
    auto *debuggerPage = new DebuggerView(this);
    auto *helpPage = new HelpView(this);
    auto *homePage = new HomeView(this);
    auto *ioPage = new IOView(this);
    auto *memoryPage = new MemoryView(this);
    auto *programmerPage = new ProgrammerView(this);
    auto *settingsPage = new SettingsView(this);

    // Create the stacked layout
    this->m_viewStack = new QStackedWidget(this);

    this->m_viewStack->addWidget(homePage);
    this->m_viewStack->addWidget(debuggerPage);
    this->m_viewStack->addWidget(memoryPage);
    this->m_viewStack->addWidget(ioPage);
    this->m_viewStack->addWidget(programmerPage);
    this->m_viewStack->addWidget(settingsPage);
    this->m_viewStack->addWidget(helpPage);

    setCentralWidget(this->m_viewStack);
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

} // namespace EtherBench::UI