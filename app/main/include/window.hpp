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
// Local libraries
#include "models/counter.hpp"

// Qt
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

namespace EtherBench::UI {

class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    explicit MainWindow(QWidget *parent = nullptr);

  private:
    void setupUI();
    void makeConnections();

    QPushButton *m_btn;
    QLabel *m_label;
    QStackedWidget *m_viewStack;

    EtherBench::Core::CounterManager m_counter;
};

} // namespace EtherBench::UI