/**
 * @file    ShellStreamTelnet.hpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Class to handle a Telnet data stream and shell.
 * @version 0.1
 * @date 2026-03-06
 *
 * @copyright Copyright (c) 2026
 *
 */

// ======================================================================
//                              INCLUDE
// ======================================================================
// Base class
#include "ShellStreamBase.hpp"

// RTOS
#include "nxd_telnet_server.h"
#include "tx_api.h"

// ======================================================================
//                              CLASS
// ======================================================================
class ShellStreamTelnet : public ShellStreamBase {
  private:
    NX_TELNET_SERVER *instance;
    UINT logical_connection;
    NX_PACKET_POOL *packet_pool;

  protected:
    void hw_transmit(const char *data, size_t length) override;

  public:
    ShellStreamTelnet(NX_PACKET_POOL *pool, char *static_buffer, size_t buffer_size)
        : ShellStreamBase(static_buffer, buffer_size, "\r\n", true), packet_pool(pool) {}

    void connect(NX_TELNET_SERVER *instance, UINT logical_connection);
    void disconnect();
};