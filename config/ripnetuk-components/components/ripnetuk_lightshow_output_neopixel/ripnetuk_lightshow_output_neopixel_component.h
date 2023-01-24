#pragma once

#include "esphome/core/component.h"
#include "../ripnetuk_ui/ripnetuk_number_component.h"
#include "../ripnetuk_clock/ripnetuk_clock_component.h"
#include <Adafruit_NeoPixel.h>
#include "../ripnetuk_lightshow_core/RGB.h"
#include "../ripnetuk_lightshow_core/base_ripnetuk_lightshow_output_component.h"
#include "esphome/core/hal.h"
#include "../ripnetuk_lightshow_core/frame.h"

namespace esphome
{
  namespace ripnetuk_lightshow_output_neopixel
  {
    class RipnetUkLightshowOutputNeopixelComponent : public Component, public ripnetuk_lightshow_core::BaseRipnetUkLightshowOutputComponent
    {
    public:
      void setup() override;
      // void set_lightshow_core(ripnetuk_lightshow_core::RipnetUkLightshowCoreComponent *core) { _core = core; }
      void set_pin(int pin) { _pin = pin; }
      void output_frame(ripnetuk_lightshow_core::Frame *frame);
      float get_setup_priority() const override;

    private:
      int _pin;
      // ripnetuk_lightshow_core::RipnetUkLightshowCoreComponent *_core;

      ripnetuk_ui::RipnetUkNumberComponent *_ha_brightness = new ripnetuk_ui::RipnetUkNumberComponent("Brightness", number::NUMBER_MODE_BOX, 0, 1, 0.001);

      Adafruit_NeoPixel *_neoPixel{nullptr};
      int scaleToByte(double value, double brightness);
    };

  } // namespace debug
} // namespace esphome
