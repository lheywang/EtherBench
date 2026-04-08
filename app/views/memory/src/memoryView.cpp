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
#include <qactiongroup.h>
#include <views/memoryView.hpp>

// Local libraries
#include <views/baseView.hpp>

// QT
#include <QActionGroup>
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

void MemoryView::fillMenubar(QMenuBar *menuBar) {

    // Add the main memory menu
    QMenu *memoryMenu = menuBar->addMenu("&Memory");
    memoryMenu->addAction("Load binary");
    memoryMenu->addAction("Load executable");
    memoryMenu->addSeparator();
    memoryMenu->addAction("Export to file");
    memoryMenu->addSeparator();
    memoryMenu->addAction("Convert to executable");
    memoryMenu->addAction("Convert to binary");

    // Add the comparison menu
    QMenu *compareMenu = menuBar->addMenu("&Compare");

    QActionGroup *slotGroup = addSlotSelection(compareMenu, "Select source");
    slotGroup->setExclusive(true);
}

} // namespace EtherBench::UI