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
#include <QPainter>

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
     * @brief Enable or disable the colorations of the cells background.
     *
     * @param color
     */
    void setDisplaMode(bool color);

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

    int cursorOffset = -1;
    int selectionStart = -1;
    int selectionEnd = -1;

    bool displayColor = true;

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
     * @param startX    The X value for the start.
     * @param y         The current Y position.
     * @param cw        Character width on pixels.
     */
    void drawHexLine(
        QPainter &p,
        const std::vector<uint8_t> &data,
        const std::vector<double> &ent,
        const std::vector<double> &der,
        int startX,
        int y,
        int cw);

    /**
     * @brief Update the scrollbar, to set where are we, and how many do wee need to show
     * !
     *
     */
    void updateScrollRange();
};

} // namespace EtherBench::UI