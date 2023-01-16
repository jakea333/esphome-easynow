#include "ripnetuk_clock_component.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "esphome/core/application.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome
{
  namespace ripnetuk_clock
  {

    static const char *TAG = "ripnetuk_clock";

    // RipnetUkClockComponent::RipnetUkClockComponent(const std::string &name)
    // {
    //   this->set_name(name);

    //   App.register_sensor(this);
    //   App.register_component(this);
    // }

    void RipnetUkClockComponent::setup()
    {
      reset();
      this->_ha_clock_speed_number->set(1);
      this->_ha_clock_pause_switch->set(false);
    }

    float RipnetUkClockComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

    void RipnetUkClockComponent::reset()
    {
      _epoch_millis = millis();
      if (_paused)
      {
        _pause_millis = _epoch_millis;
      }
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

      return virtual_millis * _speed;
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

    void RipnetUkClockComponent::update()
    {
      this->publish_state(time());
    }
  } // namespace ripnetuk_clock
} // namespace esphome
