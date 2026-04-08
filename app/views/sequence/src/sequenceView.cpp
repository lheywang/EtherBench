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

SequenceView::SequenceView(QWidget *parent) : BaseView(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Sequences", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

/*
 * Overrides from the base class
 */
QString SequenceView::viewTitle() const { return "Sequencer"; }
void SequenceView::onActivated() { qDebug() << "Welcome to sequencer"; }
void SequenceView::onDeactivated() { qDebug() << "Exiting ..."; }
void SequenceView::fillMenubar(QMenuBar *menuBar) {

    // Builder
    QMenu *buildMenu = menuBar->addMenu("&Build");
    buildMenu->addAction("Open source");
    buildMenu->addAction("Save source");
    buildMenu->addSeparator();
    buildMenu->addAction("Compile");
    buildMenu->addAction("Decompile");
    buildMenu->addSeparator();
    buildMenu->addAction("Save to device");
    buildMenu->addAction("Load from device");

    // Memory IO
    QMenu *saveMenu = menuBar->addMenu("&Memory");
    saveMenu->addAction("Save to slot");
}

} // namespace EtherBench::UI