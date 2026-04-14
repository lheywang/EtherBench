/**
 * @file    memoryHexView.cpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   hex viewer impl
 * @version 0.1
 * @date    2026-04-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
// Header
#include "../private/memoryHexView.hpp"

// Local libraries
#include <models/memoryPool.hpp>
#include <services/bufferAnalyse.hpp>

// Qt
#include <QAbstractScrollArea>
#include <QColor>
#include <QFont>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QScrollBar>

// STD
#include <algorithm>

namespace EtherBench::UI {

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

HexViewWidget::HexViewWidget(QWidget *parent) : QAbstractScrollArea(parent) {

    // Configure the shortcuts policies
    viewport()->setFocusPolicy(Qt::StrongFocus);
    setFocusProxy(viewport());

    // Add the scrollbar
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    updateScrollRange();
}

void HexViewWidget::setData(EtherBench::Models::BufferSlot target) {
    mainBuffer = target;

    // Fetch buffer parameters
    auto &pool = EtherBench::Models::MemoryPool::instance();
    auto type = pool.getBufferType(mainBuffer);
    auto buffer = pool.getBuffer(mainBuffer, type, EtherBench::Models::BufferIO::READ);

    bufferSize = buffer->size();

    pool.freeBuffer(mainBuffer);

    // Update the scrollbar
    updateScrollRange();
    viewport()->update();
}

void HexViewWidget::setBaseAddress(uint64_t addr) {
    baseAddress = addr;
    viewport()->update();
}

void HexViewWidget::setCompareBuffer(EtherBench::Models::BufferSlot target) {
    compareBuffer = target;
    viewport()->update();
}

void HexViewWidget::toggleDisplayMode() {
    displayColor = !displayColor;
    viewport()->update();
}

void HexViewWidget::toggleCompMode() {
    compareEnabled = !compareEnabled;
    viewport()->update();
}

void HexViewWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(viewport());
    painter.setFont(QFont("FiraCode-Regular", 12));

    // Fetch some sizes
    QFontMetrics fm = painter.fontMetrics();
    cw = fm.horizontalAdvance("0");
    lineHeight = fm.height() + 2;

    // Compute number of colums we need :
    int xAddr = 10;
    xHex = xAddr + (cw * 10);

    // Enter render loop
    int firstLine = verticalScrollBar()->value();
    int visibleLines = viewport()->height() / lineHeight;
    int lastLine = firstLine + visibleLines + 1;

    // Fetch the MemoryPool instance
    auto &pool = EtherBench::Models::MemoryPool::instance();
    auto type = pool.getBufferType(mainBuffer);
    auto buffer = pool.getBuffer(mainBuffer, type, EtherBench::Models::BufferIO::READ);

    auto compareType = pool.getBufferType(compareBuffer);
    auto comp =
        pool.getBuffer(compareBuffer, compareType, EtherBench::Models::BufferIO::READ);

    // Fetch our comp vector. We'll fill it, or not.
    std::vector<uint8_t> compData;
    compData.reserve(16 + 3);

    // Perform the lines rendering
    for (int line = firstLine; line < lastLine; ++line) {
        uint64_t offset = line * 16;
        int y = (line - firstLine + 1) * lineHeight;

        painter.setPen(Qt::darkGray);
        QString addrStr =
            QString("%1").arg(baseAddress + offset, 8, 16, QChar('0')).toUpper();
        painter.drawText(xAddr, y, addrStr);

        auto lineData = buffer->get(offset, 16 + 3);

        if (compareEnabled)
            compData = comp->get(offset, 16 + 3);

        auto entropyVal = EtherBench::Services::entropy(lineData, 4, 1);
        auto derivVal = EtherBench::Services::derivative(lineData, 4, 1);

        drawHexLine(painter, lineData, compData, entropyVal, derivVal, y, line);
    }

    // Free the buffer
    pool.freeBuffer(mainBuffer);
}

void HexViewWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        selectionStart = selectionEnd = offsetAt(event->pos());
        isSelecting = true;
        viewport()->update();
    }
}

void HexViewWidget::mouseMoveEvent(QMouseEvent *event) {
    if (isSelecting) {

        int64_t targetEnd = offsetAt(event->pos());
        int64_t diff = targetEnd - selectionStart;

        if (std::abs(diff) >= 32) {
            selectionEnd = selectionStart + (diff > 0 ? 31 : -31);
        } else {
            selectionEnd = targetEnd;
        }

        viewport()->update();
    }
}

void HexViewWidget::setSelection(uint64_t start, uint64_t stop) {
    selectionStart = start;
    selectionEnd = stop;
    viewport()->update();
}

void HexViewWidget::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    isSelecting = false;
    emit selectionChanged(
        std::min(selectionStart, selectionEnd), std::max(selectionEnd, selectionStart));
}

void HexViewWidget::drawHexLine(
    QPainter &p,
    const std::vector<uint8_t> &data,
    const std::vector<uint8_t> &comp,
    const std::vector<double> &ent,
    const std::vector<double> &der,
    int y,
    int line) {
    for (long unsigned int i = 0; i < 16; ++i) {

        // Ensure we did get enough data
        if (i >= data.size())
            break;

        // Get the start coordinates.
        int x = xHex + (i * cw * 3);

        // Get our rectangle, used to draw the current data
        QRect cellRect(x, y - p.fontMetrics().ascent(), cw * 2, p.fontMetrics().height());

        // Fetch the associated entropy and derivative.
        double e = (i < ent.size()) ? std::pow(ent[i], 3) : 0;
        double d = (i < der.size()) ? der[i] : 0;

        int64_t currentOffset = baseAddress + (line * 16) + i;
        int64_t selMin = std::min(selectionStart, selectionEnd);
        int64_t selMax = std::max(selectionStart, selectionEnd);

        bool isSelected = (selectionStart != -1) && (currentOffset >= selMin) &&
                          (currentOffset <= selMax);
        bool isDifferent = compareEnabled && (i < comp.size()) && (data[i] != comp[i]);

        // Conditionnal coloration
        if (isSelected) {
            p.fillRect(cellRect, QColor(0x64, 0xab, 0xf1, 255));
            p.setPen(Qt::black);

        } else {

            if (isDifferent) {
                // Write in red
                p.setPen(QColor(255, 0, 0));
            } else {
                p.setPen(Qt::white);
            }

            if (displayColor && ((e > 0.05) || (d > 0.05))) {
                int alpha = static_cast<int>(std::max(e, d) * 127);

                int r = static_cast<int>(252 * d);
                int g = static_cast<int>(87 * e + 186 * d) / 2;
                int b = static_cast<int>(179 * e);

                p.fillRect(cellRect, QColor(r, g, b, alpha));
            }
        }

        // Write the text
        QString hex = QString("%1").arg(data[i], 2, 16, QChar('0')).toUpper();
        p.drawText(cellRect, Qt::AlignCenter, hex);
    }
}

void HexViewWidget::updateScrollRange() {

    // Fetch the general properties
    int totalLines = (bufferSize + 15) / 16;
    int visibleLines = viewport()->height() / lineHeight;

    // Ensure we have enough to show
    int maxScroll = std::max(0, totalLines - visibleLines);

    if (maxScroll < 0) {
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    }

    // Configure the range
    verticalScrollBar()->setRange(0, maxScroll);
    verticalScrollBar()->setPageStep(visibleLines);
}

int64_t HexViewWidget::offsetAt(const QPoint &pos) {

    int64_t line = (pos.y() / lineHeight) + (verticalScrollBar()->value());
    int64_t col = (pos.x() - xHex) / (cw * 3);

    col = std::clamp(col, static_cast<int64_t>(0), static_cast<int64_t>(15));

    return (line * 16) + col;
}

uint64_t HexViewWidget::getStartSelection() { return selectionStart; }

uint64_t HexViewWidget::getStopSelection() { return selectionEnd; }

} // namespace EtherBench::UI