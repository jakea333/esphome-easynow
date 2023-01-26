#include "ripnetuk_lightshow_output_neopixel_component.h"
#include "esphome/core/log.h"
#include "esphome.h"
#include "../ripnetuk_lightshow_core/RGB.h"
#include "esphome/core/hal.h"

namespace esphome
{
  namespace ripnetuk_lightshow_output_neopixel
  {
    static const char *TAG = "ripnetuk_lightshow_output_neopixel";
    
    float RipnetUkLightshowOutputNeopixelComponent::get_setup_priority() const
    {
      return setup_priority::HARDWARE;
    }

    void RipnetUkLightshowOutputNeopixelComponent::setup()
    {
      _ha_brightness->set(0.1);
    }

    int RipnetUkLightshowOutputNeopixelComponent::scaleToByte(double value, double brightness)
    {
      float scaled = value * brightness * 255.0;
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

    void RipnetUkLightshowOutputNeopixelComponent::output_frame(ripnetuk_lightshow_core::Frame *frame)
    {
      if (!_neoPixel)
      {
        // FIX ME D3
        // _neoPixel = new Adafruit_NeoPixel(_core->get_pixel_count(), D3, NEO_GRB + NEO_KHZ800);
        //_neoPixel = new Adafruit_NeoPixel(frame->pixels->size(), 23, NEO_GRB + NEO_KHZ800);
        _neoPixel = new Adafruit_NeoPixel(frame->pixels->size(), this->_pin, NEO_GRB + NEO_KHZ800);

        _neoPixel->begin();
      }

      float masterBrightness = _ha_brightness->state;

      // for (int i = 0; i < _core->get_pixel_count(); i++)
      for (int i = 0; i < frame->pixels->size(); i++)
      {
        ripnetuk_lightshow_core::RGB *pxl = frame->pixels->at(i);

        int r = scaleToByte(pxl->r, masterBrightness);
        int g = scaleToByte(pxl->g, masterBrightness);
        int b = scaleToByte(pxl->b, masterBrightness);

        _neoPixel->setPixelColor(i, _neoPixel->Color(r, g, b));
        // ESP_LOGD(TAG, "%d %d %d", r, g, b);
      }
      _neoPixel->show();
    }
  }
}
