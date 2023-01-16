#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"
#include "../ripnetuk_ui/ripnetuk_switch_component.h"
#include "../ripnetuk_ui/ripnetuk_number_component.h"
#include "../ripnetuk_lightshow_core/RGB.h"
#include "../ripnetuk_lightshow_core/ripnetuk_lightshow_core_component.h"

namespace esphome
{
  namespace ripnetuk_lightshow_input_sensor
  {
    class RipnetUkLightshowInputSensorComponent : public Component
    {
    public:
      void set_sensor(sensor::Sensor *sensor) { _sensor = sensor; }
      void setup() override;
      void loop() override;
      float get_setup_priority() const override;
      void set_lightshow_core(ripnetuk_lightshow_core::RipnetUkLightshowCoreComponent *core) { _core = core; }

    private:
      sensor::Sensor *_sensor;
      ripnetuk_lightshow_core::RipnetUkLightshowCoreComponent *_core;
      ripnetuk_ui::RipnetUkSwitchComponent *_ha_use_fake_state = new ripnetuk_ui::RipnetUkSwitchComponent("Use Fake State");
      ripnetuk_ui::RipnetUkNumberComponent *_ha_fake_state = new ripnetuk_ui::RipnetUkNumberComponent("Fake State", number::NUMBER_MODE_BOX, 0, 30000, 100);

      float _currentDisplayState = 0;
      void draw();
      void drawHoldingPattern();
      void drawPower(float power);
      void drawOutOfRange(ripnetuk_lightshow_core::RGB rgb);
    };

  } // namespace debug
} // namespace esphome
