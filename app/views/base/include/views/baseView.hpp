/**
 * @file    debuggerView.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the debugger view for the EtherBenchApp project.
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
#include <QLabel>
#include <QMenuBar>
#include <QString>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

namespace EtherBench::UI {

class BaseView : public QWidget {
    Q_OBJECT

  public:
    using QWidget::QWidget;

    /*
     * Constructors and destructors
     */
    explicit BaseView(QWidget *parent = nullptr) : QWidget(parent) {}
    virtual ~BaseView() = default;

    /*
     * String based functions
     */
    virtual QString viewTitle() const = 0;

    /*
     * Window handling procedure (called when chaning the view !)
     */
    /**
     * @brief Called when the view is set as active. Can be used to fill custom logic on
     * it.
     */
    virtual void onActivated() = 0;

    /**
     * @brief Called when the view is set as inactive. Can be used to clear states.
     *
     */
    virtual void onDeactivated() = 0;

    /**
     * @brief Called right after setup, to ask for the window to fill the menubar, with
     * it's own logic.
     *
     * @param menuBar Handle to the menubar, to add menus.
     */
    virtual void fillMenubar(QMenuBar *menuBar) = 0;
};

} // namespace EtherBench::UI