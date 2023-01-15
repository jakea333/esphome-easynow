#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome
{
  namespace ripnetuk_neopixel
  {

    class RipnetUkNeopixelComponent : public Component
    {
    public:
      void set_pin(GPIOPin *pin) { _pin = pin; }
      void loop() override;
      float get_setup_priority() const override;

    private:
      GPIOPin *_pin;
    };

  } // namespace debug
} // namespace esphome
