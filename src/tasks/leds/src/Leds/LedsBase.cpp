/**
 * @file    LedsBase.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDES
// ======================================================================
// Header
#include "Leds/LedsBase.hpp"

// Local libraries
#include "Leds/LedsBaseCommands.h"

// STD
#include <cstddef>

// RTOS
#include "tx_api.h"

// ======================================================================
//                              CLASS IMPL.
// ======================================================================

LedsBase::LedsBase(TX_TIMER *timer) {
    this->timer = timer;
    return;
}

LedsBase::~LedsBase() {
    this->stop_timer();
    this->timer = nullptr;
    return;
}

UINT LedsBase::init_timer(const char *name) {

    // Just create a new timer if it was not already created.
    if (this->timer_status == 0) {
        return tx_timer_create(
            this->timer,
            const_cast<CHAR *>(name),
            LedsBase::timer_callback,
            reinterpret_cast<ULONG>(this),
            0,
            0,
            TX_NO_ACTIVATE);
    }

    return 1000;
}

UINT LedsBase::start_timer(const ULONG period_ms) {
    ULONG ticks = (period_ms * TX_TIMER_TICKS_PER_SECOND) / 1000;
    if (ticks == 0)
        ticks = 1;

    this->timer_period_ms = period_ms;

    ULONG status0 = tx_timer_change(this->timer, ticks, ticks);
    ULONG status1 = tx_timer_activate(this->timer);

    // Must return 0 anyways
    return (UINT)(status1 & status0);
}

UINT LedsBase::stop_timer() { return tx_timer_deactivate(this->timer); }