/**
 * @file    window.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Hold the main window, and it's children.
 * @version 0.1
 * @date    2026-04-02
 *
 * @copyright Copyright (c) 2026
 *
 */
#pragma once

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
// Views libraries
#include <views/baseView.hpp>
#include <views/debuggerView.hpp>
#include <views/helpView.hpp>
#include <views/homeView.hpp>
#include <views/ioView.hpp>
#include <views/memoryView.hpp>
#include <views/programmerView.hpp>
#include <views/sequenceView.hpp>
#include <views/settingsView.hpp>

#include <views/definitions/baseDefinitions.hpp>

// Models

// QT
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QPushButton>
#include <QStackedWidget>
#include <qaction.h>
#include <qapplication.h>
#include <qnamespace.h>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

// FORWARDS
class QStackedWidget;
class QAction;
class QMenu;

namespace EtherBench::UI {

// FORWARDS
class DebuggerView;
class HelpView;
class HomeView;
class IOView;
class MemoryView;
class ProgrammerView;
class SettingsView;

/**
 * @class   MainWindow  Hold the window UI, and define the most basic elements (what's
 *                      seen, menubar...)
 *
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    /*
     * Constructors and destructors
     */
    /**
     * @brief Construct a new MainWindow element.
     */
    explicit MainWindow(QWidget *parent = nullptr);

  protected:
    /**
     * @brief Ensure we fetch even if the user did close with the cross.
     *
     * @param event
     */
    void closeEvent(QCloseEvent *event) override;

  private:
    /*
     * Setup functions
     */
    /**
     * @brief Configure the UI for the MainWindow (stacked layout).
     */
    void setupUI();

    /**
     * @brief Configure the sidebar naviguation
     *
     */
    void setupSideBar();

    /**
     * @brief Configure the menubar top level.
     *
     */
    void setupMenuBar();
    void addMenuBarElements();

    /**
     * @brief Configure the connection between clickable elements,
     *        and their associated actions on the C++ part.
     *
     */
    void makeConnections();

    /*
     * Naviguation functions
     */
    /**
     * @brief Change the currently displayed view.
     *
     * @param[in] type The target index
     */
    void switchView(ViewType type);

    /*
     * Window management
     */
    static void prepare_exit();

    /**
     * @brief Exit the app. This enable us to save data before quitting.
     *
     */
    static void exit();

    /*
     * Private members, that hold pointers to elements
     */
    // Views
    QStackedWidget *m_viewStack;

    // Menus
    QMenuBar *m_menuBar;

    QMenu *fileMenu;
    QMenu *viewMenu;

    // Actions
    QAction *actHome;
    QAction *actDebugger;
    QAction *actMemory;
    QAction *actIO;
    QAction *actProgrammer;
    QAction *actSequences;
    QAction *actSettings;
    QAction *actHelp;

    // Pages
    QMap<ViewType, BaseView *> pages;

    /*
     * Private models
     */
};

} // namespace EtherBench::UI