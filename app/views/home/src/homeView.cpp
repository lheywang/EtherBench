/**
 * @file homeView.cpp
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
#include <views/homeView.hpp>

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

HomeView::HomeView(QWidget *parent) : BaseView(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Home", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

QString HomeView::viewTitle() const {
    return "Home";
}

void HomeView::onActivated() {
    qDebug() << "Welcome to home";
}

void HomeView::onDeactivated() {
    qDebug() << "Exiting ...";
}

} // namespace EtherBench::UI