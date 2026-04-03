/**
 * @file    helpView.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the help menu view for the EtherBenchApp project.
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
#include <QString>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

namespace EtherBench::UI {

class HelpView : public BaseView {
    Q_OBJECT

  public:
    explicit HelpView(QWidget *parent = nullptr);

    QString viewTitle() const override;
    void onActivated() override;
    void onDeactivated() override;
};

} // namespace EtherBench::UI