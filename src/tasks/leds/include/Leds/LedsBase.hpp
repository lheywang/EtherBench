/**
 * @file    LedsBase.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Define the base class to be used for advanced leds effects.
 * @version 0.1
 * @date    2026-03-11
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once
// ======================================================================
//                              INCLUDES
// ======================================================================
// Local libraries
#include "LedsBaseCommands.h"

// STD
#include <cstddef>

// RTOS
#include "tx_api.h"

// ======================================================================
//                              CLASS
// ======================================================================

class LedsBase {
  private:
    TX_TIMER *timer;
    bool timer_status;

  protected:
    static void timer_callback(ULONG arg);

    virtual void on_timer_tick(ULONG arg) = 0;

  public:
    /**
     * @brief Construct a new Leds Base object
     *
     * @param[in] timer         An handle to the TX_TIMER object to be used.
     */
    LedsBase(TX_TIMER *timer);

    /**
     * @brief Create and configure the timer to be used.
     *
     * @param[in] name  The name of timer to be created.
     */
    void init_timer(const char *name);

    /**
     * @brief Start the timer. Will call @ref on_timer_tick() every trigger.
     *
     * @param[in] period_ms The period to be used, in ms.
     */
    void start_timer(const ULONG period_ms);

    /**
     * @brief Stop the timer.
     *
     */
    void stop_timer();
}