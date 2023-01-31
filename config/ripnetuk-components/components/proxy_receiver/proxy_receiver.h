#pragma once

#include "esphome/core/component.h"
#include "../proxy_base/proxy_base.h"

namespace esphome
{
  namespace proxy_receiver
  {

    class ProxyReceiverComponent : public proxy_base::ProxyBaseComponent
    {
    protected:
      void handle_received_proxy_message(proxy_base::proxy_message *message) override;

    public:
      void loop() override;
      void setup() override;
    };

  } // namespace proxy_receiver
} // namespace esphome
