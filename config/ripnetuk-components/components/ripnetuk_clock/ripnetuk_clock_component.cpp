#include "ripnetuk_clock_component.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
// #include "esphome/core/application.h"

namespace esphome
{
  namespace ripnetuk_clock
  {

    static const char *TAG = "ripnetuk_clock";

    void RipnetUkClockComponent::setup()
    {
      speed = 1;
      reset();
      _last_log_millis = millis();
      ESP_LOGD(TAG, "CONSTRUCTOR");
    }

    void RipnetUkClockComponent::loop()
    {
      if (_ha_clock_reset->state)
      {
        reset();
      }
      setPaused(_ha_clock_pause->state);

      // Want to log a tick every LOG_INTERVAL ms
      if (millis() - _last_log_millis >= LOG_INTERVAL)
      {
        int currentTime = time();
        ESP_LOGD(TAG, "............................................................................(%d)", currentTime);
        _last_log_millis = millis();
      }
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
      // speed = _ha_clock_speed->state;

      int virtual_millis = millis();

      if (_paused)
      {
        virtual_millis = _pause_millis;
      }

      // Adust for epoch
      virtual_millis -= _epoch_millis;

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
