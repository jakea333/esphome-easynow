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

    RipnetUkSwitchComponent::RipnetUkSwitchComponent(const std::string &name)
    {
      this->set_name(name);
      this->set_component_source("RipnetUKSwitch");
      App.register_switch(this);
      App.register_component(this);
    }

    void RipnetUkSwitchComponent::write_state(bool state)
    {
      _deviceSideState = state;
      this->publish_state(state);
    }

    bool RipnetUkSwitchComponent::assumed_state()
    {
      return this->_deviceSideState;
    }

    float RipnetUkSwitchComponent::get_setup_priority() const
    {
      return setup_priority::HARDWARE;
    }

    void RipnetUkSwitchComponent::setup()
    {
      _deviceSideState = false;
    }
  } // namespace template_
} // namespace esphome
