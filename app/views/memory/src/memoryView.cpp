/**
 * @file memoryView.cpp
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
#include <qactiongroup.h>
#include <views/memoryView.hpp>

// Local libraries
#include <services/bufferAnalyse.hpp>
#include <views/baseView.hpp>

// Private libraries
#include "../private/memoryHexView.hpp"

// QT
#include <QActionGroup>
#include <QDebug>
#include <QLabel>
#include <QMenuBar>
#include <QRandomGenerator>
#include <QScrollBar>
#include <QSplitter>
#include <QString>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>

// STD
#include <vector>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------
namespace EtherBench::UI {

MemoryView::MemoryView(QWidget *parent) : BaseView(parent) {

    layout = new QVBoxLayout(this);
    masterSplitter = new QSplitter(Qt::Horizontal, this);

    // Call the sub elements inits
    setHexEditors();
    setHexAnalyse();

    // Add the sub elements
    masterSplitter->addWidget(tableSplitter);
    masterSplitter->addWidget(analysisTree);

    masterSplitter->setStretchFactor(0, 1);
    masterSplitter->setStretchFactor(1, 0);

    layout->addWidget(masterSplitter);
}

QString MemoryView::viewTitle() const { return "Memory"; }

void MemoryView::onActivated() {
    qDebug() << "Welcome to memory - Loading test data";

    // Fetch the MemoryPool instance
    auto &pool = EtherBench::Models::MemoryPool::instance();
    auto type1 = pool.getBufferType(EtherBench::Models::BufferSlot::SLOT1);

    auto buffer1 = pool.getBuffer(
        EtherBench::Models::BufferSlot::SLOT1,
        type1,
        EtherBench::Models::BufferIO::WRITE);

    std::vector<uint8_t> testData(0);
    testData.reserve(16384);

    for (int i = 0; i < 16384; ++i) {
        testData[i] = static_cast<char>(QRandomGenerator::global()->bounded(256));
    }

    buffer1->set(0, testData);
    pool.freeBuffer(EtherBench::Models::BufferSlot::SLOT1);

    viewA->setData(EtherBench::Models::BufferSlot::SLOT1);
}

void MemoryView::onDeactivated() { qDebug() << "Exiting ..."; }

void MemoryView::fillMenubar(QMenuBar *menuBar) {

    // Add the main memory menu
    QMenu *memoryMenu = menuBar->addMenu("&Memory");
    memoryMenu->addAction("Load binary");
    memoryMenu->addAction("Load executable");
    memoryMenu->addSeparator();
    memoryMenu->addAction("Export to file");
    memoryMenu->addSeparator();
    memoryMenu->addAction("Convert to executable");
    memoryMenu->addAction("Convert to binary");
    memoryMenu->addSeparator();

    QActionGroup *slotGroup = addSlotSelection(memoryMenu, "Select main source");
    slotGroup->setExclusive(true);

    // Add the comparison menu
    QMenu *compareMenu = menuBar->addMenu("&Compare");

    QActionGroup *slotCompareGroup =
        addSlotSelection(compareMenu, "Select comparison source");
    slotCompareGroup->setExclusive(true);

    QAction *toggleCompare = compareMenu->addAction("Enable Dual View");
    toggleCompare->setCheckable(true);

    connect(toggleCompare, &QAction::toggled, this, [this](bool enabled) {
        if (enabled) {
            viewB->show();
            // Connect the scrollbars, to they'll changed together
            connect(
                viewA->verticalScrollBar(),
                &QScrollBar::valueChanged,
                viewB->verticalScrollBar(),
                &QScrollBar::setValue);
            connect(
                viewB->verticalScrollBar(),
                &QScrollBar::valueChanged,
                viewA->verticalScrollBar(),
                &QScrollBar::setValue);
        } else {
            viewB->hide();
            viewA->verticalScrollBar()->disconnect(viewB->verticalScrollBar());
        }
    });
}

void MemoryView::setHexEditors() {

    tableSplitter = new QSplitter(Qt::Horizontal, masterSplitter);

    // Create instances
    viewA = new HexViewWidget(this);
    viewB = new HexViewWidget(this);

    // Add them to the list
    tableSplitter->addWidget(viewA);
    tableSplitter->addWidget(viewB);

    // Hide viewB
    viewB->hide();

    // Comfigure sizes
    viewA->setMinimumSize(200, 200);
}

void MemoryView::setHexAnalyse() {
    analysisTree = new QTreeView(masterSplitter);
    analysisTree->setMinimumSize(100, 100);
}

} // namespace EtherBench::UI