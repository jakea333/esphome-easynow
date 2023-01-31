#pragma once

#include "esphome/core/component.h"
#include "../proxy_base/proxy_base.h"

namespace esphome
{
  namespace proxy_transmitter
  {

    class ProxyTransmitterComponent : public proxy_base::ProxyBaseComponent
    {
    private:
      int last_testmessage_millis{0};

    protected:
      void handle_received_proxy_message(const uint8_t *mac_addr, proxy_base::proxy_message *message) override;

    public:
      void loop() override;
      void setup() override;
    };

  } // namespace proxy_transmitter
} // namespace esphome
