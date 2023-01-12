#include "ripnetuk_clock_component.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace ripnetuk_clock
  {

    static const char *TAG = "ripnetuk_clock";

    void RipnetUkClockComponent::setup()
    {
      // _ha_clock_reset = new template_::TemplateSwitch();
      // App.register_switch(_ha_clock_reset);
      // _ha_clock_reset->set_name("Clock Reset");
      // _ha_clock_reset->set_disabled_by_default(false);
      // _ha_clock_reset->set_restore_mode(switch_::SWITCH_RESTORE_DEFAULT_OFF);
      // _ha_clock_reset->set_component_source("template.switch");
      // App.register_component(_ha_clock_reset);
      // _ha_clock_reset->set_optimistic(true);
      // _ha_clock_reset->set_assumed_state(false);
      // _ha_clock_reset->set_restore_state(false);

      // _ha_clock_pause = new template_::TemplateSwitch();
      // App.register_switch(_ha_clock_pause);
      // _ha_clock_pause->set_name("Clock Pause");
      // _ha_clock_pause->set_disabled_by_default(false);
      // _ha_clock_pause->set_restore_mode(switch_::SWITCH_RESTORE_DEFAULT_OFF);
      // _ha_clock_pause->set_component_source("template.switch");
      // App.register_component(_ha_clock_pause);
      // _ha_clock_pause->set_optimistic(true);
      // _ha_clock_pause->set_assumed_state(false);
      // _ha_clock_pause->set_restore_state(false);

      // _ha_clock_speed = new template_::TemplateNumber();
      // _ha_clock_speed->set_update_interval(60000);
      // _ha_clock_speed->set_component_source("template.number");
      // App.register_component(_ha_clock_speed);
      // App.register_number(_ha_clock_speed);
      // _ha_clock_speed->set_name("Clock Speed");
      // _ha_clock_speed->set_disabled_by_default(false);
      // _ha_clock_speed->traits.set_min_value(0.0f);
      // _ha_clock_speed->traits.set_max_value(2.0f);
      // _ha_clock_speed->traits.set_step(0.1f);
      // _ha_clock_speed->traits.set_mode(number::NUMBER_MODE_AUTO);
      // _ha_clock_speed->set_optimistic(true);
      // _ha_clock_speed->set_initial_value(1.0f);

      speed = 1;
      reset();
      _last_log_millis = millis();
      ESP_LOGD(TAG, "CONSTRUCTOR");
    }

    float RipnetUkClockComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

    void RipnetUkClockComponent::reset()
    {
      ESP_LOGD(TAG, "RESET");
      _epoch_millis = millis();
    }

    int RipnetUkClockComponent::time()
    {
      if (_ha_clock_reset->state)
      {
        reset();
      }
      setPaused(_ha_clock_pause->state);
      speed = _ha_clock_speed->state;

      int virtual_millis = millis();

      if (_paused)
      {
        virtual_millis = _pause_millis;
      }

      // Adust for epoch
      virtual_millis -= _epoch_millis;

      // Want to log a tick every LOG_INTERVAL ms
      if (millis() - _last_log_millis >= LOG_INTERVAL)
      {
        ESP_LOGD(TAG, "..................................................................(%d)..........E(%d)", virtual_millis, _epoch_millis);
        _last_log_millis = millis();
      }

      return virtual_millis * speed;
    }

    void RipnetUkClockComponent::setPaused(bool is_paused)
    {
      // If already correct state, quit
      if (_paused == is_paused)
      {
        return;
      }

      if (is_paused)
      {
        _pause_millis = millis();
        _paused = true;
      }
      else
      {
        // Adjust epoch so as pause never happened...
        _epoch_millis += (millis() - _pause_millis);
        _paused = false;
      }
    }
  } // namespace ripnetuk_clock
} // namespace esphome
