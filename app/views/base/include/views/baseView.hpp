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
    virtual void onActivated() = 0;
    virtual void onDeactivated() = 0;
};

} // namespace EtherBench::UI