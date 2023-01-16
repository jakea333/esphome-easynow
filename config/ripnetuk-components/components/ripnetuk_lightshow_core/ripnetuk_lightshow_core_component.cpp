#include "ripnetuk_neopixel_component.h"
#include "esphome/core/log.h"
#include "esphome.h"

#define RANGESIZE 1500

namespace esphome
{
  namespace ripnetuk_lightshow_core
  {
    static const char *TAG = "ripnetuk_neopixel";

    void RipnetUkLightshowCoreComponent::setup()
    {
      _ha_use_fake_power->set(false);
      _ha_fake_power->set(500);
      _ha_brightness->set(0.01);
      // FIX ME
      _neoPixel = new Adafruit_NeoPixel(_pixel_count, D3, NEO_GRB + NEO_KHZ800);

      _neoPixel->begin();
    }

    float RipnetUkLightshowCoreComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

    void RipnetUkLightshowCoreComponent::loop()
    {
      draw();

      animateColors();
      showPixels();
    }

    void RipnetUkLightshowCoreComponent::draw()
    {
      float realPower = _power_sensor->state;
      float fakePower = _ha_fake_power->state;
      bool useFakePower = _ha_use_fake_power->state;

      if (isnan(realPower))
      {
        drawHoldingPattern();
      }
      else
      {
        float measuredPower = useFakePower ? fakePower : realPower;

        float deltaNeeded = measuredPower - _currentDisplayPower;
        // Limit change speed to get an animation
        float maxDelta = RANGESIZE / _pixel_count * 2; // 4 led per cycle

        float deltaToApply = deltaNeeded;
        if (deltaToApply > maxDelta)
        {
          deltaToApply = maxDelta;
        }
        if (deltaToApply < (0 - maxDelta))
        {
          deltaToApply = 0 - maxDelta;
        }
        _currentDisplayPower += deltaToApply;
        drawPower(_currentDisplayPower);
      }
    }

    int RipnetUkLightshowCoreComponent::scaleToByte(double value, double brightness)
    {
      float scaled = value * brightness * 255;
      int asInt = scaled;
      if (asInt < 0)
      {
        asInt = 0;
      }
      if (asInt > 255)
      {
        asInt = 255;
      }
      // ESP_LOGD("ScaleToByte value: %f2 brightness: %f2 result: %d", value, brightness, asInt);
      return asInt;
    }

    void RipnetUkLightshowCoreComponent::showPixels()
    {
      float masterBrightness = _ha_brightness->state;

      for (int i = 0; i < _pixel_count; i++)
      {
        RGB pxl = _pixels[i];
        float overallBrightness = pxl.brightness * masterBrightness;

        int r = scaleToByte(pxl.r, overallBrightness);
        int g = scaleToByte(pxl.g, overallBrightness);
        int b = scaleToByte(pxl.b, overallBrightness);

        _neoPixel->setPixelColor(i, _neoPixel->Color(r, g, b));
      }
      _neoPixel->show();
    }

    void RipnetUkLightshowCoreComponent::drawHoldingPattern()
    {
      int activeLed = (_clock->time() / 200) % _pixel_count;

      for (int i = 0; i < _pixel_count; i++)
      {
        RGB pxl = OFF_PIXEL;

        pxl.r = 0;
        pxl.g = 0;
        pxl.b = 0;
        pxl.brightness = 1;

        if (WiFi.status() != WL_CONNECTED)
        {
          pxl.b = (i == activeLed) ? 1 : 0;
        }
        else
        {
          pxl.g = (i == activeLed) ? 1 : 0;
        }
        _pixels[i] = pxl;
      }
    }

    void RipnetUkLightshowCoreComponent::drawOutOfRange(RGB rgb)
    {
      bool isOn = ((_clock->time() / 500) % 2) != 0;
      for (int i = 0; i < _pixel_count; i++)
      {
        _pixels[i] = isOn ? rgb : OFF_PIXEL;
      }
    }

    void RipnetUkLightshowCoreComponent::drawPower(float power)
    {
      int rangeRGBCount = sizeof(rangeRGBs) / sizeof(rangeRGBs[0]);

      // Figure out which range we are in...
      int rangeIndex = power / RANGESIZE;
      // ESP_LOGD(TAG, "Draw Power %f range index %d", power, rangeIndex);
      //  Check we are in range...
      if (power < 0)
      {
        drawOutOfRange({1, 0, 0, 1});
        return;
      }
      if (rangeIndex >= rangeRGBCount)
      {
        drawOutOfRange({1, 1, 1, 1});
        return;
      }

      float rangeStart = rangeIndex * RANGESIZE;

      float positionInRange = power - rangeStart;

      // We reseerve 1 LED so we can anlways tell what range is

      float lengthPerLED = RANGESIZE / (_pixel_count - 1);

      int ledsToLight = positionInRange / lengthPerLED;
      float remainder = positionInRange - (ledsToLight * lengthPerLED);

      float remainderBrightness = remainder / lengthPerLED;

      // ESP_LOGD(TAG, "Measured Power %f - PositionInRange %f - rangeLength %f - lengthPerLED %f - remainder %f -- LEDS to Light %d remainderBrightness %f", power, positionInRange, rangeLength, lengthPerLED, remainder, ledsToLight, remainderBrightness);

      auto rangeRGB = rangeRGBs[rangeIndex];

      for (int i = 0; i < _pixel_count; i++)
      {
        RGB pxl = OFF_PIXEL;
        // Always light first one
        if (i == 0)
        {
          pxl = rangeRGB;
        }
        // Light up completely filled lights
        if (i <= ledsToLight)
        {
          pxl = rangeRGB;
        }
        // Light up next LED as remainer
        if (i == ledsToLight + 1)
        {
          pxl = rangeRGB;
          pxl.brightness = remainder / lengthPerLED;
        }
        _pixels[i] = pxl;
      }
    }

    int flashPeriod = 16000;
    float flareMaxStrength = 2;

    void RipnetUkLightshowCoreComponent::animateColors()
    {
      int rangeRGBCount = sizeof(rangeRGBs) / sizeof(rangeRGBs[0]);
      int flareIndex = (_clock->time() / 10000) % rangeRGBCount;
      auto flareRGB = rangeRGBs[flareIndex];
      flareRGB.r = 1 - flareRGB.r;
      flareRGB.g = 1 - flareRGB.g;
      flareRGB.b = 1 - flareRGB.b;

      int wholePeriods = (_clock->time() / flashPeriod);
      float msIntoCurrentPeriod = _clock->time() - flashPeriod * wholePeriods;
      // Make is ossocilate between 0 and half period
      if (msIntoCurrentPeriod > (flashPeriod / 2))
      {
        msIntoCurrentPeriod = flashPeriod - msIntoCurrentPeriod;
      }

      // scale 0-HP to 0 - flareMaxStrength
      float flareStrength = (msIntoCurrentPeriod / (flashPeriod / 2)) * flareMaxStrength;

      // Darken the flare color to flareStrength
      flareRGB.r *= flareStrength;
      flareRGB.g *= flareStrength;
      flareRGB.b *= flareStrength;

      // ESP_LOGD(TAG, "CANGES !!! msIntoCurrentPeriod %f FlareStrenctg %f flare r %f  g %f  b %f ", msIntoCurrentPeriod, flareStrength, flareRGB.r, flareRGB.g, flareRGB.b);

      for (int i = 0; i < _pixel_count; i++)
      {
        if ((_pixels[i].r == 0) && (_pixels[i].g == 0) && (_pixels[i].b == 0))
          continue; // Dont mess with black as its obvious and anoying
        _pixels[i].r = (_pixels[i].r + flareRGB.r) / 2;
        _pixels[i].g += (_pixels[i].g + flareRGB.g) / 2;
        _pixels[i].b += (_pixels[i].b + flareRGB.b) / 2;
      }
    }
  }
}
