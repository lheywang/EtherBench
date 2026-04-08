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
#include <qboxlayout.h>
#include <qtextbrowser.h>
#include <views/baseView.hpp>

// QT
#include <QDebug>
#include <QLabel>
#include <QMenuBar>
#include <QString>
#include <QTextBrowser>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

namespace EtherBench::UI {

class HelpView : public BaseView {
    Q_OBJECT

  public:
    explicit HelpView(QWidget *parent = nullptr);

    /*
     * Overrides
     */
    QString viewTitle() const override;
    void onActivated() override;
    void onDeactivated() override;
    void fillMenubar(QMenuBar *menuBar) override;

  private:
    /*
     * Standard functions
     */
    void setupUI();
    void makeConnections();

    /*
     * Private variables
     */
    QVBoxLayout *m_layout;
    QTextBrowser *m_browser;
};

} // namespace EtherBench::UI