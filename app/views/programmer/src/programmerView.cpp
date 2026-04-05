/**
 * @file programmerView.cpp
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
#include <views/programmerView.hpp>

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

ProgrammerView::ProgrammerView(QWidget *parent) : BaseView(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Programmer", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

QString ProgrammerView::viewTitle() const { return "Programmer"; }

void ProgrammerView::onActivated() { qDebug() << "Welcome to programmer"; }

void ProgrammerView::onDeactivated() { qDebug() << "Exiting ..."; }

void ProgrammerView::fillMenubar(QMenuBar *menuBar) { return; }

} // namespace EtherBench::UI