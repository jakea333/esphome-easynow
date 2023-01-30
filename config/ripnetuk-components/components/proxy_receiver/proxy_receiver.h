#pragma once

#include "esphome/core/component.h"

namespace esphome
{
  namespace proxy_receiver
  {

    class ProxyReceiverComponent : public Component
    {
    public:
      float get_setup_priority() const override;
      void loop() override;
    };

  } // namespace proxy_receiver
} // namespace esphome
