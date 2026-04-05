/**
 * @file    ioView.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the home menu view for the EtherBenchApp project.
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
// Local libraries
#include <views/baseView.hpp>

// QT
#include <QLabel>
#include <QMenuBar>
#include <QString>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

namespace EtherBench::UI {

class IOView : public BaseView {
    Q_OBJECT

  public:
    explicit IOView(QWidget *parent = nullptr);

    QString viewTitle() const override;
    void onActivated() override;
    void onDeactivated() override;
    void fillMenubar(QMenuBar *menuBar) override;
};

} // namespace EtherBench::UI