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
#include <views/sequenceView.hpp>

// Local libraries
#include <views/baseView.hpp>

// QT
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <qboxlayout.h>
#include <qnamespace.h>
#include <qwidget.h>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------
namespace EtherBench::UI {

SequenceView::SequenceView(QWidget *parent) : BaseView(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Sequences", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

QString SequenceView::viewTitle() const {
    return "Sequencer";
}

void SequenceView::onActivated() {
    qDebug() << "Welcome to sequencer";
}

void SequenceView::onDeactivated() {
    qDebug() << "Exiting ...";
}

} // namespace EtherBench::UI