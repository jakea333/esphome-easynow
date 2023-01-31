#pragma once

#include "esphome/core/component.h"
#include "../proxy_base/proxy_base.h"

namespace esphome
{
  namespace proxy_receiver
  {

    class ProxyReceiverComponent : public proxy_base::ProxyBaseComponent
    {
    public:
      void loop() override;
      void setup() override;
    };

  } // namespace proxy_receiver
} // namespace esphome
