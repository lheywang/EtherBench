#pragma once

#include "models/counter.hpp"
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

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

    // Logique métier
    EtherBench::Core::CounterManager m_counter;
};

} // namespace EtherBench::UI