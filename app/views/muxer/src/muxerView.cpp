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
#include <views/muxerView.hpp>

// Local libraries
#include <views/baseView.hpp>

// QT
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QMenuBar>
#include <QStandardPaths>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------
namespace EtherBench::UI {

MuxerView::MuxerView(QWidget *parent) : BaseView(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Muxer", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

/*
 * Overrides from the base class
 */
QString MuxerView::viewTitle() const { return "Muxer"; }
void MuxerView::onActivated() { qDebug() << "Welcome to muxer"; }
void MuxerView::onDeactivated() { qDebug() << "Exiting ..."; }
void MuxerView::fillMenubar(QMenuBar *menuBar) { return; }

} // namespace EtherBench::UI