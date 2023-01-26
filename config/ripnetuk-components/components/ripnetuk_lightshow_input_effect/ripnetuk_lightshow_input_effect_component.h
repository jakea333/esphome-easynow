#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"
#include "../ripnetuk_ui/ripnetuk_switch_component.h"
#include "../ripnetuk_ui/ripnetuk_number_component.h"
#include "../ripnetuk_lightshow_core/RGB.h"
#include "../ripnetuk_lightshow_core/ripnetuk_lightshow_core_component.h"
#include "../ripnetuk_lightshow_core/base_ripnetuk_lightshow_input_component.h"
#include "../ripnetuk_lightshow_core/frame.h"

namespace esphome
{
  namespace ripnetuk_lightshow_input_effect
  {
    class RipnetUkLightshowInputEffectComponent : public Component, public ripnetuk_lightshow_core::BaseRipnetUkLightshowInputComponent
    {
    public:
      void setup() override;
      void input_frame(ripnetuk_lightshow_core::Frame *frame, ripnetuk_lightshow_core::Frame *output_frame_so_far);
      float get_setup_priority() const override;

    private:
      ripnetuk_ui::RipnetUkNumberComponent *_ha_effect = new ripnetuk_ui::RipnetUkNumberComponent("Effect", number::NUMBER_MODE_BOX, 0, 30, 1);
       ripnetuk_ui::RipnetUkNumberComponent *_ha_s = new ripnetuk_ui::RipnetUkNumberComponent("Effect S", number::NUMBER_MODE_BOX, 0, 1, 0.1);
        ripnetuk_ui::RipnetUkNumberComponent *_ha_v = new ripnetuk_ui::RipnetUkNumberComponent("Effect V", number::NUMBER_MODE_BOX, 0, 1, 0.1);
    };

  } // namespace 
} // namespace esphome
