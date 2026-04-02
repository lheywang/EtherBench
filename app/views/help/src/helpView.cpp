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
#include <views/helpView.hpp>

// Local libraries
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

HelpView::HelpView(QWidget *parent) : QWidget(parent) {

    auto *layout = new QVBoxLayout(this);
    auto *label = new QLabel("Help", this);

    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

} // namespace EtherBench::UI