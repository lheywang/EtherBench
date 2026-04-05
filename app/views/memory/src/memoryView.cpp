/**
 * @file memoryView.cpp
 * @author lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date 2026-04-02
 *
 * @copyright Copyright (c) 2026
 *
 */

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
// Header
#include <views/memoryView.hpp>

// Local libraries
#include <views/baseView.hpp>

// QT
#include <QDebug>
#include <QLabel>
#include <QMenuBar>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------
namespace EtherBench::UI {

MemoryView::MemoryView(QWidget *parent) : BaseView(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Memory", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

QString MemoryView::viewTitle() const { return "Memory"; }

void MemoryView::onActivated() { qDebug() << "Welcome to memory"; }

void MemoryView::onDeactivated() { qDebug() << "Exiting ..."; }

void MemoryView::fillMenubar(QMenuBar *menuBar) { return; }

} // namespace EtherBench::UI