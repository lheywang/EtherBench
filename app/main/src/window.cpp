#include "window.hpp"
#include <QVBoxLayout>

namespace EtherBench::UI {

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    makeConnections();
}

void MainWindow::setupUI() {
    setWindowTitle("EtherBench MWE");
    resize(300, 200);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);

    m_label = new QLabel("Compteur : 0", this);
    m_label->setAlignment(Qt::AlignCenter);

    m_btn = new QPushButton("Incrémenter", this);
    m_btn->setMinimumHeight(40);

    layout->addWidget(m_label);
    layout->addWidget(m_btn);
    setCentralWidget(central);
}

void MainWindow::makeConnections() {
    connect(
        m_btn,
        &QPushButton::clicked,
        &m_counter,
        &EtherBench::Core::CounterManager::increment);

    connect(
        &m_counter,
        &EtherBench::Core::CounterManager::countChanged,
        this,
        [this](int val) { m_label->setText(QString("Compteur : %1").arg(val)); });
}

} // namespace EtherBench::UI