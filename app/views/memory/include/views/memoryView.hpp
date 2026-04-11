/**
 * @file    memoryView.hpp
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

// Private libraries
#include "../../private/memoryHexView.hpp"

// QT
#include <QLabel>
#include <QMenuBar>
#include <QSplitter>
#include <QString>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

namespace EtherBench::UI {

class MemoryView : public BaseView {
    Q_OBJECT

  public:
    explicit MemoryView(QWidget *parent = nullptr);

    QString viewTitle() const override;
    void onActivated() override;
    void onDeactivated() override;
    void fillMenubar(QMenuBar *menuBar) override;

  private:
    /*
     * Private variables
     */
    QVBoxLayout *layout;
    QSplitter *masterSplitter;
    QSplitter *tableSplitter;

    HexViewWidget *viewA;
    HexViewWidget *viewB;
    QTreeView *analysisTree;

    /*
     * Private functions
     */
    void setHexEditors();
    void setHexAnalyse();
};

} // namespace EtherBench::UI