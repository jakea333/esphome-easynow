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

    RipnetUkNumberComponent::RipnetUkNumberComponent(const std::string &name, number::NumberMode mode, float min_value, float max_value, float step, std::function<void(float state)> on_change)
    {
      this->set_name(name);
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
       ESP_LOGD(TAG, "...control.........................................................................(%f)", state);
      this->_on_change(state);
      _deviceSideState = state;
      this->publish_state(state);
    }

    void RipnetUkNumberComponent::setup()
    {
      control(_deviceSideState);
    }

    void RipnetUkNumberComponent::set(float state)
    {
      this->control(state);
    }
  } // namespace template_
} // namespace esphome
