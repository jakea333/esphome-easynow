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
      void input_frame(ripnetuk_lightshow_core::Frame *frame);
      float get_setup_priority() const override;

    private:
      // ripnetuk_ui::RipnetUkSwitchComponent *_ha_use_fake_state = new ripnetuk_ui::RipnetUkSwitchComponent("Use Fake State");
      // ripnetuk_ui::RipnetUkNumberComponent *_ha_fake_state = new ripnetuk_ui::RipnetUkNumberComponent("Fake State", number::NUMBER_MODE_BOX, 0, 30000, 100);
    };

  } // namespace 
} // namespace esphome
