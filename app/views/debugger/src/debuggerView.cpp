/**
 * @file    debuggerView.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-04-02
 *
 * @copyright Copyright (c) 2026
 *
 */

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
// Header
#include <views/debuggerView.hpp>

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

DebuggerView::DebuggerView(QWidget *parent) : BaseView(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Debugger", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

QString DebuggerView::viewTitle() const { return "Debugger"; }

void DebuggerView::onActivated() { qDebug() << "Welcome to debugger"; }

void DebuggerView::onDeactivated() { qDebug() << "Exiting ..."; }

void DebuggerView::fillMenubar(QMenuBar *menuBar) { return; }

} // namespace EtherBench::UI