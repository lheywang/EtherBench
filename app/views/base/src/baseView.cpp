/**
 * @file    baseView.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the most standard BaseView functions.
 * @version 0.1
 * @date    2026-04-08
 *
 * @copyright Copyright (c) 2026
 *
 */

// =============================================================
// INCLUDES
// =============================================================
// Header
#include <views/baseView.hpp>

// Qt
#include <QAction>
#include <QActionGroup>
#include <QMenu>
#include <QMenuBar>
#include <QString>

// =============================================================
// CLASS
// =============================================================

namespace EtherBench::UI {

QActionGroup *BaseView::addSlotSelection(QMenu *parent, QString title) {

    QMenu *slotSelector = parent->addMenu(title);
    auto *slotGroup = new QActionGroup(this);

    for (int i = 0; i < 8; i += 1) {
        // Add the action to the list
        QString name = QString("Slot %1").arg(i + 1);
        QAction *act = slotSelector->addAction(name);

        // Configure it
        act->setCheckable(true);
        act->setData(i);
        slotGroup->addAction(act);
    }

    return slotGroup;
}

} // namespace EtherBench::UI