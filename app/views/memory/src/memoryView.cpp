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
#include <qkeysequence.h>
#include <qnamespace.h>
#include <views/memoryView.hpp>

// Local libraries
#include <services/bufferAnalyse.hpp>
#include <views/baseView.hpp>

// Private libraries
#include "../private/memoryHexView.hpp"
#include "models/memoryPool.hpp"

// QT
#include <QActionGroup>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLabel>
#include <QMenuBar>
#include <QObject>
#include <QRandomGenerator>
#include <QScrollBar>
#include <QShortcut>
#include <QSplitter>
#include <QString>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>

// STD
#include <algorithm>
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

    // Fetch the MemoryPool instance
    auto &pool = EtherBench::Models::MemoryPool::instance();
    auto type1 = pool.getBufferType(EtherBench::Models::BufferSlot::SLOT1);

    auto buffer1 = pool.getBuffer(
        EtherBench::Models::BufferSlot::SLOT1,
        type1,
        EtherBench::Models::BufferIO::WRITE);
    auto buffer2 = pool.getBuffer(
        EtherBench::Models::BufferSlot::SLOT2,
        type1,
        EtherBench::Models::BufferIO::WRITE);

    std::vector<uint8_t> testData(0);
    testData.reserve(16384);
    std::vector<uint8_t> testData2(0);
    testData2.reserve(16384);

    for (int i = 0; i < 16384; ++i) {
        char val = static_cast<char>(QRandomGenerator::global()->bounded(256));
        testData.push_back(val);
        testData2.push_back(val);
    }
    for (int i = 0; i < 16384; ++i) {
        if (i % 128 == 0)
            testData2[i] = static_cast<char>(QRandomGenerator::global()->bounded(256));
    }

    buffer1->set(0, testData);
    buffer2->set(0, testData2);

    pool.freeBuffer(EtherBench::Models::BufferSlot::SLOT1);
    pool.freeBuffer(EtherBench::Models::BufferSlot::SLOT2);

    viewA->setData(EtherBench::Models::BufferSlot::SLOT1);
    viewA->setCompareBuffer(EtherBench::Models::BufferSlot::SLOT2);

    viewB->setData(EtherBench::Models::BufferSlot::SLOT2);
    viewB->setCompareBuffer(EtherBench::Models::BufferSlot::SLOT1);

    slotA = EtherBench::Models::BufferSlot::SLOT1;
    slotB = EtherBench::Models::BufferSlot::SLOT2;

    // Finally, add the shortcuts
    setShortcuts();
}

void MemoryView::onDeactivated() { qDebug() << "Exiting ..."; }

void MemoryView::fillMenubar(QMenuBar *menuBar) {

    /*
     * Add the main elements :
     */
    QMenu *memoryMenu = menuBar->addMenu("&Memory");
    memoryMenu->addAction("Load binary");
    memoryMenu->addAction("Load executable");
    memoryMenu->addSeparator();
    memoryMenu->addAction("Export to file");
    memoryMenu->addSeparator();
    memoryMenu->addAction("Convert to executable");
    memoryMenu->addAction("Convert to binary");
    memoryMenu->addSeparator();

    /*
     * Source selection
     */
    QActionGroup *slotGroup = addSlotSelection(memoryMenu, "Select main source");
    slotGroup->setExclusive(true);

    connect(slotGroup, &QActionGroup::triggered, this, [this](QAction *action) {
        int slotID = action->data().toInt();
        slotA = static_cast<EtherBench::Models::BufferSlot>(slotID);
        viewA->setData(slotA);
    });

    /*
     * Buffer configurion
     */
    // Buffer coloration
    QAction *toggleColor = memoryMenu->addAction("Toggle buffer color");
    toggleColor->setCheckable(true);
    toggleColor->setChecked(true);

    connect(toggleColor, &QAction::toggled, this, [this]() {
        viewA->toggleDisplayMode();
        viewB->toggleDisplayMode();
    });

    /*
     * Buffer comparison menu
     */
    QMenu *compareMenu = menuBar->addMenu("&Compare");

    QActionGroup *slotCompareGroup =
        addSlotSelection(compareMenu, "Select comparison source");
    slotCompareGroup->setExclusive(true);

    QAction *toggleCompare = compareMenu->addAction("Enable Dual View");
    toggleCompare->setCheckable(true);

    // Connect the callback when the data is changed
    connect(slotCompareGroup, &QActionGroup::triggered, this, [this](QAction *action) {
        int slotID = action->data().toInt();
        slotB = static_cast<EtherBench::Models::BufferSlot>(slotID);
        viewB->setData(slotB);
    });

    // Ensure scrollbars are linked together.
    connect(toggleCompare, &QAction::toggled, this, [this](bool enabled) {
        if (enabled) {
            viewB->show();
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

    /*
     * Buffer coloration menu
     */
    QAction *toggleComp = compareMenu->addAction("Toggle buffer comparison");
    toggleComp->setCheckable(true);
    toggleComp->setChecked(false);

    connect(toggleComp, &QAction::toggled, this, [this, toggleCompare]() {
        viewA->toggleCompMode();
        viewB->toggleCompMode();
        toggleCompare->setChecked(true);
        compareEnabled = !compareEnabled;
    });

    /*
     * Difference search
     */
    compareMenu->addSeparator();
    QAction *findNextDiff = compareMenu->addAction("Find next diff\tF3");
    connect(findNextDiff, &QAction::triggered, this, &MemoryView::findNextDifference);
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

    // Link the selection togethers
    connect(
        viewA,
        &HexViewWidget::selectionChanged,
        this,
        [this](uint64_t start, uint64_t stop) { viewB->setSelection(start, stop); });
    connect(
        viewB,
        &HexViewWidget::selectionChanged,
        this,
        [this](uint64_t start, uint64_t stop) { viewA->setSelection(start, stop); });
}

void MemoryView::setHexAnalyse() {
    analysisTree = new QTreeView(masterSplitter);
    analysisTree->setMinimumSize(100, 100);
}

void MemoryView::setShortcuts() {

    QWidget *win = window();

    QShortcut *f3 = new QShortcut(QKeySequence(Qt::Key_F3), win);
    f3->setContext(Qt::WindowShortcut);

    connect(f3, &QShortcut::activated, this, &MemoryView::findNextDifference);
}

bool MemoryView::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_F3) {
            findNextDifference();
            return true;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void MemoryView::findNextDifference() {

    // Ensure all conditions are met
    if ((slotA == EtherBench::Models::BufferSlot::SLOT_COUNT) ||
        (slotB == EtherBench::Models::BufferSlot::SLOT_COUNT) || (!compareEnabled)) {
        return;
    }

    // Fetch the buffers
    auto &pool = EtherBench::Models::MemoryPool::instance();
    auto bufferA = pool.getBuffer(
        slotA, pool.getBufferType(slotA), EtherBench::Models::BufferIO::READ);
    auto bufferB = pool.getBuffer(
        slotB, pool.getBufferType(slotB), EtherBench::Models::BufferIO::READ);

    if (!bufferA || !bufferB)
        return;

    // Fetch the first byte, or the current selection.
    uint64_t startOffset = std::max(
        static_cast<uint64_t>((viewA->verticalScrollBar()->value() * 16)),
        viewA->getStartSelection());
    startOffset += 1; // Increment to not re-land on the current selection.

    // Get the usefull comparison range
    uint64_t size = std::min(bufferA->size(), bufferB->size());
    if (startOffset >= size) {
        return;
    }

    // iterate over the data (as large chunks of few kB)
    uint64_t chunk_size = (1ULL << 16); // 64 KB
    uint64_t currentOffset = startOffset;

    while (currentOffset < size) {

        // Fetch the next size of data
        uint64_t processSize = std::min(size - currentOffset, chunk_size);

        // Fetch the data
        auto dataA = bufferA->get(currentOffset, processSize);
        auto dataB = bufferB->get(currentOffset, processSize);

        // Search for differences
        auto [itA, itB] =
            std::mismatch(dataA.begin(), dataA.end(), dataB.begin(), dataB.end());

        if (itA != dataA.end()) {
            uint64_t relativeOffset = std::distance(dataA.begin(), itA);
            uint64_t absoluteOffset = currentOffset + relativeOffset;

            // We found a different byte, thus, process it
            viewA->verticalScrollBar()->setValue(absoluteOffset / 16);
            viewB->verticalScrollBar()->setValue(absoluteOffset / 16);

            viewA->setSelection(absoluteOffset, absoluteOffset);
            viewB->setSelection(absoluteOffset, absoluteOffset);

            return;
        }

        currentOffset += processSize;
    }
}

} // namespace EtherBench::UI