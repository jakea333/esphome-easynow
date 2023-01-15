#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"

namespace esphome
{
  namespace ripnetuk_neopixel
  {

    class RipnetUkNeopixelComponent : public Component
    {
    public:
      void set_pin(GPIOPin *pin) { _pin = pin; }
      void set_pixel_count(int pixel_count) { _pixel_count = pixel_count; }
      void set_power_sensor(sensor::Sensor *power_sensor) { _power_sensor = power_sensor; }
      void loop() override;
      float get_setup_priority() const override;

    private:
      GPIOPin *_pin;
      int _pixel_count;
      sensor::Sensor *_power_sensor;
    };

  } // namespace debug
} // namespace esphome



// namespace esphome
// {
//     namespace neopixel_lightshow_component
//     {
//         class NeoPixelLightShowComponent : public Component
//         {
//         private:
//             template_::TemplateSwitch *_ha_use_fake_power;
//             template_::TemplateNumber *_ha_brightness;
//             template_::TemplateNumber *_ha_fake_power;
//             NeoPixelLightShowConfig *_config;
//             Adafruit_NeoPixel *_neoPixel;
//             RGB _pixels[200]; // TODO: MAKE THIS NICER but for now I only have 144 max...
//             int _lastUpdateMillis = 0;
//             float _currentDisplayPower = 0;
//             LedClock *_clock;

//             int scaleToByte(double value, double brightness);
//             void draw();
//             void drawHoldingPattern();
//             void drawPower(float power);
//             void drawOutOfRange(RGB rgb);
//             void showPixels();
//             void animateColors();

//         public:
//             NeoPixelLightShowComponent(NeoPixelLightShowConfig *config);
//             void setup() override;
//             void loop() override;
//         };
//     }
// }
