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

    RipnetUkNumberComponent::RipnetUkNumberComponent(const std::string &name, std::function<void(bool state)> on_change)
    {
      this->_on_change = on_change;
      this->set_name(name);
      this->set_component_source("RipnetUKNumber");
      App.register_number(this);
      App.register_component(this);
    }

    void RipnetUkNumberComponent::control(float state)
    {
      if (state != _deviceSideState)
      {
        this->_on_change(state);
      }

      _deviceSideState = state;
      this->publish_state(state);
    }

    float RipnetUkNumberComponent::get_setup_priority() const
    {
      return setup_priority::HARDWARE;
    }

    void RipnetUkNumberComponent::setup()
    {
      _deviceSideState = nan;
    }
  } // namespace template_
} // namespace esphome
