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

    public:
      void loop() override;
      void setup() override;
    };

  } // namespace proxy_transmitter
} // namespace esphome
