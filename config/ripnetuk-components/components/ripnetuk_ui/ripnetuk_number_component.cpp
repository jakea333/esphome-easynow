#include "ripnetuk_number_component.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome
{
  namespace ripnetuk_ui
  {

    static const char *TAG = "ripnetuk_number";

    RipnetUkNumberComponent::RipnetUkNumberComponent()
    {
    }

    RipnetUkNumberComponent::RipnetUkNumberComponent(const std::string &name, float initial_state, number::NumberMode mode, float min_value, float max_value, float step, std::function<void(float state)> on_change)
    {
      this->set_name(name);
      this->_deviceSideState = initial_state;
      this->traits.set_mode(mode);
      this->traits.set_min_value(min_value);
      this->traits.set_max_value(max_value);
      this->traits.set_step(step);
      this->_on_change = on_change;

      this->set_component_source("RipnetUKNumber");

      App.register_number(this);
      App.register_component(this);
    }

    void RipnetUkNumberComponent::control(float state)
    {
      if (state != _deviceSideState)
      {
        this->_on_change(state);
        _deviceSideState = state;
      }
      this->publish_state(state);
    }

    float RipnetUkNumberComponent::get_setup_priority() const
    {
      return setup_priority::HARDWARE;
    }

    void RipnetUkNumberComponent::setup()
    {
      control(_deviceSideState);
    }
  } // namespace template_
} // namespace esphome

//  _ha_clock_speed->set_update_interval(60000);
//       _ha_clock_speed->set_component_source("template.number");
//       App.register_component(_ha_clock_speed);
//       App.register_number(_ha_clock_speed);
//       _ha_clock_speed->set_name("Clock Speed");
//       _ha_clock_speed->set_disabled_by_default(false);
//       _ha_clock_speed->traits.set_min_value(0.0f);
//       _ha_clock_speed->traits.set_max_value(2.0f);
//       _ha_clock_speed->traits.set_step(0.1f);
//       _ha_clock_speed->traits.set_mode(number::NUMBER_MODE_AUTO);
//       _ha_clock_speed->set_optimistic(true);
//       _ha_clock_speed->set_initial_value(1.0f);