#pragma once

#include "esphome/components/switch/switch.h"
#include "esphome/core/component.h"
#include "../ripnetuk_ui/ripnetuk_switch_component.h"
#include "../ripnetuk_ui/ripnetuk_button_component.h"

#define LOG_INTERVAL 1000

namespace esphome
{
  namespace ripnetuk_clock
  {
    class RipnetUkClockSwitch;

    class RipnetUkClockComponent : public Component
    {
    private:
      float speed;
      ripnetuk_ui::RipnetUkSwitchComponent *_ha_clock_reset = new ripnetuk_ui::RipnetUkSwitchComponent("Clock Reset");
      ripnetuk_ui::RipnetUkSwitchComponent *_ha_clock_pause = new ripnetuk_ui::RipnetUkSwitchComponent("Clock Pause");
      ripnetuk_ui::RipnetUkButtonComponent *_ha_test_button = new ripnetuk_ui::RipnetUkButtonComponent("Test Button");
      // template_::Number *_ha_clock_speed;
      int _epoch_millis;
      int _last_log_millis;
      int _pause_millis;
      bool _paused;

    public:
      int time();
      void reset();
      void setPaused(bool is_paused);

      void setup() override;
      void loop() override;
      float get_setup_priority() const override;
    };
  } // namespace debug
} // namespace esphome
