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
#include <QPainter>
#include <QRect>
#include <QScrollBar>

namespace EtherBench::UI {

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

HexViewWidget::HexViewWidget(QWidget *parent) : QAbstractScrollArea(parent) {}

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
    update();
}

void HexViewWidget::setBaseAddress(uint64_t addr) {
    baseAddress = addr;
    update();
}

void HexViewWidget::setCompareBuffer(EtherBench::Models::BufferSlot target) {
    compareBuffer = target;
    update();
}

void HexViewWidget::setDisplaMode(bool color) {
    displayColor = color;
    update();
}

void HexViewWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(viewport());
    painter.setFont(QFont("FiraCode-Regular", 12));

    // Fetch some sizes
    QFontMetrics fm = painter.fontMetrics();
    int charWidth = fm.horizontalAdvance("0");
    int lineHeight = fm.height() + 2;

    // Compute number of colums we need :
    int xAddr = 10;
    int xHex = xAddr + (charWidth * 10);

    // Enter render loop
    int firstLine = verticalScrollBar()->value();
    int visibleLines = viewport()->height() / lineHeight;
    int lastLine = firstLine + visibleLines + 1;

    // Fetch the MemoryPool instance
    auto &pool = EtherBench::Models::MemoryPool::instance();
    auto type = pool.getBufferType(mainBuffer);
    auto buffer = pool.getBuffer(mainBuffer, type, EtherBench::Models::BufferIO::READ);

    // Perform the lines rendering
    for (int line = firstLine; line < lastLine; ++line) {
        uint64_t offset = line * 16;
        int y = (line - firstLine + 1) * lineHeight;

        painter.setPen(Qt::darkGray);
        QString addrStr =
            QString("%1").arg(baseAddress + offset, 8, 16, QChar('0')).toUpper();
        painter.drawText(xAddr, y, addrStr);

        auto lineData = buffer->get(offset, 16 + 3);

        auto entropyVal = EtherBench::Services::entropy(lineData, 4, 1);
        auto derivVal = EtherBench::Services::derivative(lineData, 4, 1);

        drawHexLine(painter, lineData, entropyVal, derivVal, xHex, y, charWidth);
    }

    // Free the buffer
    pool.freeBuffer(mainBuffer);
}

void HexViewWidget::mousePressEvent(QMouseEvent *event) { Q_UNUSED(event;) }

void HexViewWidget::mouseMoveEvent(QMouseEvent *event) { Q_UNUSED(event;) }

void HexViewWidget::drawHexLine(
    QPainter &p,
    const std::vector<uint8_t> &data,
    const std::vector<double> &ent,
    const std::vector<double> &der,
    int startX,
    int y,
    int cw) {
    for (long unsigned int i = 0; i < 16; ++i) {

        // Ensure we did get enough data
        if (i >= data.size())
            break;

        // Get the start coordinates.
        int x = startX + (i * cw * 3);

        // Get our rectangle, used to draw the current data
        QRect cellRect(x, y - p.fontMetrics().ascent(), cw * 2, p.fontMetrics().height());

        // Fetch the associated entropy and derivative.
        double e = (i < ent.size()) ? ent[i] : 0;
        double d = (i < der.size()) ? der[i] : 0;

        // Get the color (default to black)

        QColor color(0, 0, 0, 255);
        QColor red(252, 186, 3);  // Orange
        QColor blue(12, 87, 179); // Cyan

        if (displayColor) {
            color.setRed((red.red() * d + blue.red() * e) / (d + e + 0.001));
            color.setGreen((red.green() * d + blue.green() * e) / (d + e + 0.001));
            color.setBlue((red.blue() * d + blue.blue() * e) / (d + e + 0.001));

            // Max --> Better render
            color.setAlpha(static_cast<int>(std::max(d, e) * 80));
        }

        // Fill the rectangle
        p.fillRect(cellRect, color);

        // Write the text
        p.setPen(Qt::white);
        QString hex = QString("%1").arg(data[i], 2, 16, QChar('0')).toUpper();
        p.drawText(cellRect, Qt::AlignCenter, hex);
    }
}

void HexViewWidget::updateScrollRange() {

    int totalLines = (bufferSize + 15) / 16;
    int visibleLines = viewport()->height() / lineHeight;

    verticalScrollBar()->setRange(0, qMax(0, totalLines - visibleLines));
    verticalScrollBar()->setPageStep(visibleLines);
}

} // namespace EtherBench::UI