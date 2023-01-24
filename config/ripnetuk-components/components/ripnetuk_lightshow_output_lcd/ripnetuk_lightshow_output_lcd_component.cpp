#include "ripnetuk_lightshow_output_lcd_component.h"
#include "esphome/core/log.h"
#include "esphome.h"

// #include "SPI.h"
// #include <Adafruit_GFX.h>
// #include <Adafruit_ILI9341.h>

// #define TFT_DC 21
// #define TFT_CS 22
// #define TFT_MOSI 23
// #define TFT_CLK 19
// #define TFT_RST 18
// #define TFT_MISO 13

// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
//  If using the breakout, change pins as desired
// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

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
      // tft.begin();
      _ha_test->set(false);
    }

    void RipnetUkLightshowOutputLcdComponent::output_frame(ripnetuk_lightshow_core::Frame *frame)
    {
      if (_ha_test->state)
      {
        ESP_LOGD(TAG, "Frame start %d", frame->time);
        run_test();
        ESP_LOGD(TAG, "....Frame End %d", frame->time);
      }
    }

    void RipnetUkLightshowOutputLcdComponent::run_test()
    {
      // tft.fillScreen(millis() % 0xFFFF);
    }
  }
}

// # spi:
// #   clk_pin: 19
// #   mosi_pin: 23
// #   miso_pin: 25 /// NOW 13

// i2c:
//   sda: 26
//   scl: 25
//   #   cs_pin: 22
//   #   dc_pin: 21
//   #   reset_pin: 18