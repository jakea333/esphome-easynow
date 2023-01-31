#pragma once

#include "esphome/core/component.h"

namespace esphome
{
  namespace proxy_base
  {

    class ProxyBaseComponent : public Component
    {
    private:
      int last_log_millis_{0};

    public:
      float get_setup_priority() const override;
      void loop() override;
    };

  } // namespace proxy_base
} // namespace esphome
