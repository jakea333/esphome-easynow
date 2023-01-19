#pragma once

#include "../ripnetuk_lightshow_core/base_ripnetuk_lightshow_output_component.h"
#include "../ripnetuk_lightshow_core/frame.h"

namespace esphome
{
  namespace ripnetuk_lightshow_output_lcd
  {
    class RipnetUkLightshowOutputLcdComponent : public ripnetuk_lightshow_core::BaseRipnetUkLightshowOutputComponent
    {
    public:
      void setup() override;
      void output_frame(ripnetuk_lightshow_core::Frame *frame);
    private:

    };

  } // namespace debug
} // namespace esphome
