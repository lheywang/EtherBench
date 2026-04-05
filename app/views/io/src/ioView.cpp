/**
 * @file ioView.cpp
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
#include <views/ioView.hpp>

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

IOView::IOView(QWidget *parent) : BaseView(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("IO", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

QString IOView::viewTitle() const { return "Serial IO"; }

void IOView::onActivated() { qDebug() << "Welcome to serial IO"; }

void IOView::onDeactivated() { qDebug() << "Exiting ..."; }

void IOView::fillMenubar(QMenuBar *menuBar) { return; }

} // namespace EtherBench::UI