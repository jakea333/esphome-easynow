#pragma once

#include "esphome/components/template/switch/template_switch.h"
#include "esphome/components/template/number/template_number.h"
#include "esphome/core/component.h"

#define LOG_INTERVAL 1000

namespace esphome
{
  namespace ripnetuk_clock
  {
    class RipnetUkClockComponent : public Component
    {
    private:
      float speed;
      template_::TemplateSwitch *_ha_clock_reset;
      template_::TemplateSwitch *_ha_clock_paus;
      template_::TemplateNumber *_ha_clock_speed;
      int _epoch_millis;
      int _last_log_millis;
      int _pause_millis;
      bool _paused;

    public:
      int time();
      void reset();
      void setPaused(bool is_paused);

      void setup() override;
      float get_setup_priority() const override;
    };

  } // namespace debug
} // namespace esphome

