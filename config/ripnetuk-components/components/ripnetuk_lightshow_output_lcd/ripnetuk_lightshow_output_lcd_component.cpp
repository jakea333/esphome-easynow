#include "ripnetuk_lightshow_output_lcd_component.h"
#include "esphome/core/log.h"
#include "esphome.h"

namespace esphome
{
  namespace ripnetuk_lightshow_output_lcd
  {
    static const char *TAG = "ripnetuk_lightshow_output_lcd";

    float RipnetUkLightshowOutputLcdComponent::get_setup_priority() const
    {
      return setup_priority::HARDWARE;
    }

    void RipnetUkLightshowOutputLcdComponent::setup()
    {
      set_buffer_color_mode(ili9341::BITS_8);
      ILI9341TFT24::setup();
      _ha_test->set(false);
    }

    void RipnetUkLightshowOutputLcdComponent::update()
    {
      // Do nothing here
    }

    int RipnetUkLightshowOutputLcdComponent::scale_to_byte(double value, double brightness)
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

    void RipnetUkLightshowOutputLcdComponent::output_frame(ripnetuk_lightshow_core::Frame *frame)
    {
      int col_width = 1;

      float lcd_pixels_per_frame_pixel = this->get_height() / frame->pixels->size();

      for (int i = 0; i < frame->pixels->size(); i++)
      {
        int x0 = x;
        int y0 = i * lcd_pixels_per_frame_pixel;
        int w = col_width;
        int h = lcd_pixels_per_frame_pixel;
        auto frame_color = frame->pixels->at(i);
        Color c = Color(scale_to_byte(frame_color->r, frame_color->brightness), scale_to_byte(frame_color->g, frame_color->brightness), scale_to_byte(frame_color->b, frame_color->brightness));
        this->filled_rectangle(x0, y0, w, h, c);
      }

      x += col_width;
      if (x > this->get_width())
      {
        x = 0;
      }
      this->display_();
    }

    void RipnetUkLightshowOutputLcdComponent::run_test()
    {
      Color c = Color(millis() % 0xFFFF);
      this->fill(c);
    }
  }
}
