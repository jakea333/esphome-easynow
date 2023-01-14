#include "ripnetuk_button_component.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome
{
  namespace ripnetuk_ui
  {

    static const char *TAG = "ripnetuk_button";

    RipnetUkButtonComponent::RipnetUkButtonComponent()
    {
    }

    RipnetUkButtonComponent::RipnetUkButtonComponent(const std::string &name, std::function<void()> on_click)
    {
      this->_on_click = on_click;
      this->set_name(name);
      this->set_component_source("RipnetUKButton");
      App.register_button(this);
      App.register_component(this);
    }

    void RipnetUkButtonComponent::press_action()
    {
      if (this->_on_click)
      {
        this->_on_click();
      }
    }

    float RipnetUkButtonComponent::get_setup_priority() const
    {
      return setup_priority::HARDWARE;
    }
  } // namespace template_
} // namespace esphome
