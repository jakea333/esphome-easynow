#pragma once

#include "esphome/core/component.h"

namespace esphome
{
  namespace ripnetuk_clock
  {

    class RipnetUkClockComponent : public PollingComponent
    {
    public:
      void setup() override;
      void update() override;
      float get_setup_priority() const override;
    };

  } // namespace debug
} // namespace esphome
