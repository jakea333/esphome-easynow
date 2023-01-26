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
  namespace ripnetuk_lightshow_input_sensor
  {
    class RipnetUkLightshowInputSensorComponent : public Component, public ripnetuk_lightshow_core::BaseRipnetUkLightshowInputComponent
    {
    public:
      void set_sensor(sensor::Sensor *sensor) { _sensor = sensor; }
      void setup() override;
      void input_frame(ripnetuk_lightshow_core::Frame *frame, ripnetuk_lightshow_core::Frame *output_frame_so_far);
      float get_setup_priority() const override;

    private:
      sensor::Sensor *_sensor;
      ripnetuk_ui::RipnetUkSwitchComponent *_ha_use_fake_state = new ripnetuk_ui::RipnetUkSwitchComponent("Use Fake State");
      ripnetuk_ui::RipnetUkNumberComponent *_ha_fake_state = new ripnetuk_ui::RipnetUkNumberComponent("Fake State", number::NUMBER_MODE_BOX, 0, 30000, 100);

      float _currentDisplayState = 0;
      void drawHoldingPattern(ripnetuk_lightshow_core::Frame *frame);
      void drawPower(ripnetuk_lightshow_core::Frame *frame, float power);
      void drawOutOfRange(ripnetuk_lightshow_core::Frame *frame, ripnetuk_lightshow_core::RGB *rgb);
    };

  } // namespace debug
} // namespace esphome
