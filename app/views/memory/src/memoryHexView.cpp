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
    QPainter painter(viewport());
    painter.setFont(QFont("FiraCode-Regular", 12));

    // Fetch some sizes
    QFontMetrics fm = painter.fontMetrics();
    int charWidth = fm.horizontalAdvance("0");
    int lineHeight = fm.height() + 2;

    // Compute number of colums we need :
    int xAddr = 10;
    int xHex = xAddr + (charWidth * 10);
    int xAscii = xHex + (charWidth * 3 * 16);

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

void HexViewWidget::mousePressEvent(QMouseEvent *event) {}

void HexViewWidget::mouseMoveEvent(QMouseEvent *event) {}

void HexViewWidget::drawHexLine(
    QPainter &p,
    const std::vector<uint8_t> &data,
    const std::vector<double> &ent,
    const std::vector<double> &der,
    int startX,
    int y,
    int cw) {
    for (int i = 0; i < 16; ++i) {

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
        int r = 0;
        int g = 0;
        int b = 0;
        int alpha = 255;

        if (displayColor) {
            r = static_cast<int>(255 * d);
            g = static_cast<int>(255 * e * 0.8 + 165 * d * 0.5);
            b = static_cast<int>(255 * e);
            alpha = static_cast<int>(std::max(e, d) * 150);
        }

        // Fill the rectangle
        p.fillRect(cellRect, QColor(r, g, b, alpha));

        // Write the text
        p.setPen(alpha > 100 ? Qt::white : Qt::black);
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