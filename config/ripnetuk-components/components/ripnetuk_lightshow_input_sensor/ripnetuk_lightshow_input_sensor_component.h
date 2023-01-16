// #pragma once

// #include "esphome/core/component.h"
// #include "esphome/components/sensor/sensor.h"
// #include "esphome/core/hal.h"
// #include "../ripnetuk_ui/ripnetuk_switch_component.h"
// #include "../ripnetuk_ui/ripnetuk_number_component.h"
// #include "ripnetuk_clock_component.h"
// #include <Adafruit_NeoPixel.h>
// #include "RGB.h"

// namespace esphome
// {
//   namespace ripnetuk_neopixel
//   {
//     class RipnetUkNeopixelComponent : public Component
//     {
//     public:
//       void set_pin(GPIOPin *pin) { _pin = pin; }
//       void set_pixel_count(int pixel_count) { _pixel_count = pixel_count; }
//       void set_power_sensor(sensor::Sensor *power_sensor) { _power_sensor = power_sensor; }
//       void setup() override;
//       void loop() override;
//       float get_setup_priority() const override;

//     private:
//       GPIOPin *_pin;
//       int _pixel_count;
//       sensor::Sensor *_power_sensor;

//       RipnetUkClockComponent *_clock = new RipnetUkClockComponent("Clock");
//       ripnetuk_ui::RipnetUkSwitchComponent *_ha_use_fake_power = new ripnetuk_ui::RipnetUkSwitchComponent("Use Fake Power");
//       ripnetuk_ui::RipnetUkNumberComponent *_ha_fake_power = new ripnetuk_ui::RipnetUkNumberComponent("Fake Power", number::NUMBER_MODE_BOX, 0, 30000, 100);
//       ripnetuk_ui::RipnetUkNumberComponent *_ha_brightness = new ripnetuk_ui::RipnetUkNumberComponent("Brightness", number::NUMBER_MODE_BOX, 0, 1, 0.001);

//       Adafruit_NeoPixel *_neoPixel;
//       RGB _pixels[200]; // TODO: MAKE THIS NICER but for now I only have 144 max...
//       float _currentDisplayPower = 0;
//       int scaleToByte(double value, double brightness);
//       void draw();
//       void drawHoldingPattern();
//       void drawPower(float power);
//       void drawOutOfRange(RGB rgb);
//       void showPixels();
//       void animateColors();
//     };

//   } // namespace debug
// } // namespace esphome
