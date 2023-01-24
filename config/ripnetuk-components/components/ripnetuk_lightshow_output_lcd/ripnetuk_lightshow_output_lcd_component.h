#pragma once

#include "../ripnetuk_lightshow_core/base_ripnetuk_lightshow_output_component.h"
#include "../ripnetuk_lightshow_core/frame.h"
#include "../ripnetuk_ui/ripnetuk_switch_component.h"
#include "../ripnetuk_ui/ripnetuk_button_component.h"

namespace esphome
{
  namespace ripnetuk_lightshow_output_lcd
  {
    class RipnetUkLightshowOutputLcdComponent : public Component, public ripnetuk_lightshow_core::BaseRipnetUkLightshowOutputComponent
    {
    public:
      void setup() override;
      void output_frame(ripnetuk_lightshow_core::Frame *frame);
      float get_setup_priority() const override;
      
    private:
      ripnetuk_ui::RipnetUkSwitchComponent *_ha_test = new ripnetuk_ui::RipnetUkSwitchComponent("Test");
      ripnetuk_ui::RipnetUkButtonComponent *_ha_clock_reset_button = new ripnetuk_ui::RipnetUkButtonComponent("Run Test", [this]
                                                                                                              { this->run_test(); });
      void run_test();
    };

  } // namespace debug
} // namespace esphome
