/**
 * @file    sequenceView.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Implement the debugger view for the EtherBenchApp project.
 * @version 0.1
 * @date    2026-04-02
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

// ----------------------------------------------------------------------
// INCLUDES
// ----------------------------------------------------------------------
#include <QLabel>
#include <QString>
#include <QWidget>

// ----------------------------------------------------------------------
// CLASS
// ----------------------------------------------------------------------

namespace EtherBench::UI {

class SequenceView : public QWidget {
    Q_OBJECT

  public:
    explicit SequenceView(QWidget *parent = nullptr);
};

} // namespace EtherBench::UI