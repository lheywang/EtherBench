/**
 * @file    memoryHexView.hpp
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   hex viewer impl
 * @version 0.1
 * @date    2026-04-11
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
// Local libraries
#include <models/memoryPool.hpp>

// Qt
#include <QAbstractScrollArea>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>

namespace EtherBench::UI {
// ----------------------------------------------------------------------
// class
// ----------------------------------------------------------------------

class HexViewWidget : public QAbstractScrollArea {
    Q_OBJECT
  public:
    /*
     * Constructors and destructors
     */
    /**
     * @brief Construct a new Hex View Widget object
     *
     * @param parent
     */
    explicit HexViewWidget(QWidget *parent = nullptr);

    /**
     * @brief Set the data stored into the buffer, with it's associated entropy.
     *
     * @param target    The target slot we received. We'll fetch data for you !
     */
    void setData(EtherBench::Models::BufferSlot target);

    /**
     * @brief Set the base address of the data. Used to show the user where is he looking.
     *
     * @param addr      The current address;
     */
    void setBaseAddress(uint64_t addr);

    /**
     * @brief Set the compared buffer.
     *
     * @param target Set the target slot against which we'll compare the first buffer.
     * We'll fetch data for you !
     */
    void setCompareBuffer(EtherBench::Models::BufferSlot target);

    /**
     * @brief Toggle the colorations of the cells background.
     */
    void toggleDisplayMode();

    /**
     * @brief Toggle the colorations of the compared cells
     */
    void toggleCompMode();

    /**
     * @brief Set the selection range, used to synchronise the correct buffer togethers.
     *
     * @param start The start index.
     * @param stop  The number of selected bytes.
     */
    void setSelection(uint64_t offset, uint64_t length);

  signals:
    /**
     * @brief Emitted when we're changing the selection --> Will trigger cast update
     *
     * @param offset The current offset we selected
     * @param length The current length we selected
     */
    void selectionChanged(int offset, int length);

  protected:
    /**
     * @brief Callback called when an update is required ! Generally, on the buffer
     * openning, or on a scrollbar events
     *
     * @param event
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Callback called when the mouse is pressed.
     *
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief Callback called when the mouse has moved
     *
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief Callback when the mouse is released.
     *
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

  private:
    /*
     * Variables
     */
    EtherBench::Models::BufferSlot mainBuffer;
    EtherBench::Models::BufferSlot compareBuffer;

    uint64_t baseAddress = 0;
    uint64_t bufferSize = 0;
    int bytesPerLine = 16;
    int lineHeight = 20;

    int64_t selectionStart = -1;
    int64_t selectionEnd = -1;
    bool isSelecting = false;

    bool displayColor = true;
    bool compareEnabled = false;

    int cw;
    int xHex;

    /*
     * Functions
     */
    /**
     * @brief Draw a line of hex data.
     *
     * @param p         The current painter.
     * @param data      The data to be shown.
     * @param ent       The entropies of the data.
     * @param der       The derivatifs of the data.
     * @param y         The current Y position.
     * @param line      The current line number.
     */
    void drawHexLine(
        QPainter &p,
        const std::vector<uint8_t> &data,
        const std::vector<uint8_t> &comp,
        const std::vector<double> &ent,
        const std::vector<double> &der,
        int y,
        int line);

    /**
     * @brief Update the scrollbar, to set where are we, and how many do wee need to show
     *
     */
    void updateScrollRange();

    /**
     * @brief Handle to compute the selection.
     *
     * @param pos       The current position.
     * @return int64_t
     */
    int64_t offsetAt(const QPoint &pos);
};

} // namespace EtherBench::UI