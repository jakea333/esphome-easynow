#include "ripnetuk_lightshow_output_lcd_component.h"
#include "esphome/core/log.h"
#include "esphome.h"

#include "SPI.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_DC 21
#define TFT_CS 22
#define TFT_MOSI 23
#define TFT_CLK 19
#define TFT_RST 18
#define TFT_MISO 25


//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

namespace esphome
{
  namespace ripnetuk_lightshow_output_lcd
  {
    static const char *TAG = "ripnetuk_lightshow_output_lcd";

    void RipnetUkLightshowOutputLcdComponent::setup()
    {
      tft.begin();
    }

    void RipnetUkLightshowOutputLcdComponent::output_frame(ripnetuk_lightshow_core::Frame *frame)
    {
      tft.fillScreen(frame->time % 0xFFFF);
    }
  }
}
