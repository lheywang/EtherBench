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

#ifdef __cplusplus
extern "C" {
#endif
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
    ULONG timer_period_ms;

  protected:
    static void timer_callback(ULONG arg) {
        // When the timer does trigger, we'll just call the callback after casting it !
        LedsBase *ClassInstance = reinterpret_cast<LedsBase *>(arg);
        if (ClassInstance != nullptr) {
            ClassInstance->on_timer_tick(arg);
        }
        return;
    }

    virtual void on_timer_tick(ULONG arg) = 0;

  public:
    /**
     * @brief Construct a new Leds Base object
     *
     * @param[in] timer         An handle to the TX_TIMER object to be used.
     */
    LedsBase(TX_TIMER *timer);

    /**
     * @brief Destroy the Leds Base object
     *
     */
    ~LedsBase();

    /**
     * @brief Create and configure the timer to be used.
     *
     * @param[in] name  The name of timer to be created.
     */
    UINT init_timer(const char *name);

    /**
     * @brief Start the timer. Will call @ref on_timer_tick() every trigger.
     *
     * @param[in] period_ms The period to be used, in ms.
     */
    UINT start_timer(const ULONG period_ms);

    /**
     * @brief Stop the timer.
     *
     */
    UINT stop_timer();
};

#ifdef __cplusplus
}
#endif