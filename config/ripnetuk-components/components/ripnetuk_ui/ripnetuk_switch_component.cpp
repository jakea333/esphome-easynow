#include "ripnetuk_switch_component.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome
{
  namespace ripnetuk_ui
  {

    static const char *TAG = "ripnetuk_switch";

    RipnetUkSwitchComponent::RipnetUkSwitchComponent()
    {
    }

    RipnetUkSwitchComponent::RipnetUkSwitchComponent(const std::string &name, std::function<void(bool state)> on_change)
    {
      this->set_name(name);
      this->_on_change = on_change;

      this->set_component_source("RipnetUKSwitch");

      App.register_switch(this);
      App.register_component(this);
    }

    void RipnetUkSwitchComponent::write_state(bool state)
    {
      this->_on_change(state);
      _deviceSideState = state;
      this->publish_state(state);
    }

    bool RipnetUkSwitchComponent::assumed_state()
    {
      return false; // Dont show on AND off, since the state is known and not assumed.
    }

    void RipnetUkSwitchComponent::setup()
    {
      write_state(_deviceSideState);
    }

    void RipnetUkSwitchComponent::set(bool state)
    {
      this->write_state(state);
    }
  } // namespace template_
} // namespace esphome
