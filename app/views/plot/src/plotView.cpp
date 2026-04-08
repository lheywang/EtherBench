/**
 * @file helpView.cpp
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
#include <views/plotView.hpp>

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

PlotView::PlotView(QWidget *parent) : BaseView(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Plot", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

QString PlotView::viewTitle() const { return "Plot"; }

void PlotView::onActivated() { qDebug() << "Welcome to plotter"; }

void PlotView::onDeactivated() { qDebug() << "Exiting ..."; }

void PlotView::fillMenubar(QMenuBar *menuBar) {

    // Save
    QMenu *saveMenu = menuBar->addMenu("&Save");
    saveMenu->addAction("Save to file");
    saveMenu->addAction("Load from file");

    // Plotter menu
    QMenu *exportMenu = menuBar->addMenu("&Export");
    exportMenu->addAction("Export to CSV");
    exportMenu->addAction("Export to Matlab");
    exportMenu->addAction("Export to Python");
}

} // namespace EtherBench::UI