#include "ripnetuk_neopixel_component.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace ripnetuk_neopixel
  {
    static const char *TAG = "ripnetuk_neopixel";

    void RipnetUkNeopixelComponent::loop()
    {
     // ESP_LOGD(TAG, "neopixel Heap Size: %u bytes", free_heap);
    }

    float RipnetUkNeopixelComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

  } // namespace debug
} // namespace esphome


// #include "NeoPixelLightShowComponent.h"
// #include "RGB.h"

// static const char *TAG = "NeoPixelLightShowComponent.cppp";

// namespace esphome
// {
//     namespace neopixel_lightshow_component
//     {
//         NeoPixelLightShowComponent::NeoPixelLightShowComponent(NeoPixelLightShowConfig *config)
//         {
//             _config = config;

//             _ha_use_fake_power = new template_::TemplateSwitch();
//             App.register_switch(_ha_use_fake_power);
//             _ha_use_fake_power->set_name("Use Fake Power");
//             _ha_use_fake_power->set_disabled_by_default(false);
//             _ha_use_fake_power->set_restore_mode(switch_::SWITCH_RESTORE_DEFAULT_OFF);
//             _ha_use_fake_power->set_component_source("template.switch");
//             App.register_component(_ha_use_fake_power);
//             _ha_use_fake_power->set_optimistic(true);
//             _ha_use_fake_power->set_assumed_state(false);
//             _ha_use_fake_power->set_restore_state(false);

//             _ha_brightness = new template_::TemplateNumber();
//             _ha_brightness->set_update_interval(60000);
//             _ha_brightness->set_component_source("template.number");
//             App.register_component(_ha_brightness);
//             App.register_number(_ha_brightness);
//             _ha_brightness->set_name("Brightness");
//             _ha_brightness->set_disabled_by_default(false);
//             _ha_brightness->traits.set_min_value(0.0f);
//             _ha_brightness->traits.set_max_value(1.0f);
//             _ha_brightness->traits.set_step(0.001f);
//             _ha_brightness->traits.set_mode(number::NUMBER_MODE_AUTO);
//             _ha_brightness->set_optimistic(true);
//             _ha_brightness->set_initial_value(0.1f);

//             _ha_fake_power = new template_::TemplateNumber();
//             _ha_fake_power->set_update_interval(60000);
//             _ha_fake_power->set_component_source("template.number");
//             App.register_component(_ha_fake_power);
//             App.register_number(_ha_fake_power);
//             _ha_fake_power->set_name("Fake Power");
//             _ha_fake_power->set_disabled_by_default(false);
//             _ha_fake_power->traits.set_min_value(-10.0f);
//             _ha_fake_power->traits.set_max_value(100000.0f);
//             _ha_fake_power->traits.set_step(10.0f);
//             _ha_fake_power->traits.set_mode(number::NUMBER_MODE_AUTO);
//             _ha_fake_power->set_optimistic(true);
//             _ha_fake_power->set_initial_value(450.0f);
//         }

//         void NeoPixelLightShowComponent::setup()
//         {
//             ESP_LOGD(TAG, "Setup...");

//             _neoPixel = new Adafruit_NeoPixel(_config->led_count, _config->pin, NEO_GRB + NEO_KHZ800);

//             _neoPixel->begin();

//             _clock = new LedClock();
//             ESP_LOGD(TAG, "...End Setup");
//         }

//         void NeoPixelLightShowComponent::loop()
//         {
//             // Configure clock
//             //_clock->setPaused(id(_config->pause_clock).state);
//             //_clock->speed = id(_config->speed).state;

//             draw();

//             animateColors();
//             showPixels();
//         }

//         void NeoPixelLightShowComponent::draw()
//         {
//             // if (id(_config->reset_clock).state)
//             // {
//             //     _clock->reset();
//             //     drawHoldingPattern();
//             //     return;
//             // }

//             float realPower = id(_config->homeassistant_sensor_powermon_house_power).state;
//             float fakePower = _ha_fake_power->state;
//             bool useFakePower = _ha_use_fake_power->state;

//             if (isnan(realPower))
//             {
//                 drawHoldingPattern();
//             }
//             else
//             {
//                 float measuredPower = useFakePower ? fakePower : realPower;

//                 float deltaNeeded = measuredPower - _currentDisplayPower;
//                 // Limit change speed to get an animation
//                 float maxDelta = RANGESIZE / _config->led_count * 2; // 4 led per cycle

//                 float deltaToApply = deltaNeeded;
//                 if (deltaToApply > maxDelta)
//                 {
//                     deltaToApply = maxDelta;
//                 }
//                 if (deltaToApply < (0 - maxDelta))
//                 {
//                     deltaToApply = 0 - maxDelta;
//                 }
//                 _currentDisplayPower += deltaToApply;
//                 drawPower(_currentDisplayPower);
//             }
//         }

//         int NeoPixelLightShowComponent::scaleToByte(double value, double brightness)
//         {
//             float scaled = value * brightness * 255;
//             int asInt = scaled;
//             if (asInt < 0)
//             {
//                 asInt = 0;
//             }
//             if (asInt > 255)
//             {
//                 asInt = 255;
//             }
//             // ESP_LOGD("ScaleToByte value: %f2 brightness: %f2 result: %d", value, brightness, asInt);
//             return asInt;
//         }

//         void NeoPixelLightShowComponent::showPixels()
//         {
//             float masterBrightness = _ha_brightness->state;

//             for (int i = 0; i < _config->led_count; i++)
//             {
//                 RGB pxl = _pixels[i];
//                 float overallBrightness = pxl.brightness * masterBrightness;

//                 int r = scaleToByte(pxl.r, overallBrightness);
//                 int g = scaleToByte(pxl.g, overallBrightness);
//                 int b = scaleToByte(pxl.b, overallBrightness);

//                 _neoPixel->setPixelColor(i, _neoPixel->Color(r, g, b));
//             }
//             _neoPixel->show();
//         }

//         void NeoPixelLightShowComponent::drawHoldingPattern()
//         {
//             int activeLed = (_clock->time() / 200) % _config->led_count;

//             for (int i = 0; i < _config->led_count; i++)
//             {
//                 RGB pxl = OFF_PIXEL;

//                 pxl.r = 0;
//                 pxl.g = 0;
//                 pxl.b = 0;
//                 pxl.brightness = 1;

//                 if (WiFi.status() != WL_CONNECTED)
//                 {
//                     pxl.b = (i == activeLed) ? 1 : 0;
//                 }
//                 else
//                 {
//                     pxl.g = (i == activeLed) ? 1 : 0;
//                 }
//                 _pixels[i] = pxl;
//             }
//         }

//         void NeoPixelLightShowComponent::drawOutOfRange(RGB rgb)
//         {
//             bool isOn = ((_clock->time() / 500) % 2) != 0;
//             for (int i = 0; i < _config->led_count; i++)
//             {
//                 _pixels[i] = isOn ? rgb : OFF_PIXEL;
//             }
//         }

//         void NeoPixelLightShowComponent::drawPower(float power)
//         {
//             int rangeRGBCount = sizeof(rangeRGBs) / sizeof(rangeRGBs[0]);

//             // Figure out which range we are in...
//             int rangeIndex = power / RANGESIZE;
//             // ESP_LOGD(TAG, "Draw Power %f range index %d", power, rangeIndex);
//             //  Check we are in range...
//             if (power < 0)
//             {
//                 drawOutOfRange({1, 0, 0, 1});
//                 return;
//             }
//             if (rangeIndex >= rangeRGBCount)
//             {
//                 drawOutOfRange({1, 1, 1, 1});
//                 return;
//             }

//             float rangeStart = rangeIndex * RANGESIZE;

//             float positionInRange = power - rangeStart;

//             // We reseerve 1 LED so we can anlways tell what range is

//             float lengthPerLED = RANGESIZE / (_config->led_count - 1);

//             int ledsToLight = positionInRange / lengthPerLED;
//             float remainder = positionInRange - (ledsToLight * lengthPerLED);

//             float remainderBrightness = remainder / lengthPerLED;

//             // ESP_LOGD(TAG, "Measured Power %f - PositionInRange %f - rangeLength %f - lengthPerLED %f - remainder %f -- LEDS to Light %d remainderBrightness %f", power, positionInRange, rangeLength, lengthPerLED, remainder, ledsToLight, remainderBrightness);

//             auto rangeRGB = rangeRGBs[rangeIndex];

//             for (int i = 0; i < _config->led_count; i++)
//             {
//                 RGB pxl = OFF_PIXEL;
//                 // Always light first one
//                 if (i == 0)
//                 {
//                     pxl = rangeRGB;
//                 }
//                 // Light up completely filled lights
//                 if (i <= ledsToLight)
//                 {
//                     pxl = rangeRGB;
//                 }
//                 // Light up next LED as remainer
//                 if (i == ledsToLight + 1)
//                 {
//                     pxl = rangeRGB;
//                     pxl.brightness = remainder / lengthPerLED;
//                 }
//                 _pixels[i] = pxl;
//             }
//         }

//         int flashPeriod = 16000;
//         float flareMaxStrength = 0.12;

//         void NeoPixelLightShowComponent::animateColors()
//         {
//             int rangeRGBCount = sizeof(rangeRGBs) / sizeof(rangeRGBs[0]);
//             int flareIndex = (_clock->time() / 10000) % rangeRGBCount;
//             auto flareRGB = rangeRGBs[flareIndex];
//             flareRGB.r = 1 - flareRGB.r;
//             flareRGB.g = 1 - flareRGB.g;
//             flareRGB.b = 1 - flareRGB.b;

//             int wholePeriods = (_clock->time() / flashPeriod);
//             float msIntoCurrentPeriod = _clock->time() - flashPeriod * wholePeriods;
//             // Make is ossocilate between 0 and half period
//             if (msIntoCurrentPeriod > (flashPeriod / 2))
//             {
//                 msIntoCurrentPeriod = flashPeriod - msIntoCurrentPeriod;
//             }

//             // scale 0-HP to 0 - flareMaxStrength
//             float flareStrength = (msIntoCurrentPeriod / (flashPeriod / 2)) * flareMaxStrength;

//             // Darken the flare color to flareStrength
//             flareRGB.r *= flareStrength;
//             flareRGB.g *= flareStrength;
//             flareRGB.b *= flareStrength;

//             // ESP_LOGD(TAG, "CANGES !!! msIntoCurrentPeriod %f FlareStrenctg %f flare r %f  g %f  b %f ", msIntoCurrentPeriod, flareStrength, flareRGB.r, flareRGB.g, flareRGB.b);

//             for (int i = 0; i < _config->led_count; i++)
//             {
//                 if ((_pixels[i].r == 0) && (_pixels[i].g == 0) && (_pixels[i].b == 0))
//                     continue; // Dont mess with black as its obvious and anoying
//                 _pixels[i].r += flareRGB.r;
//                 _pixels[i].g += flareRGB.g;
//                 _pixels[i].b += flareRGB.b;
//             }
//         }

//     }
// }
