#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/button/button.h"

namespace esphome
{
  namespace ripnetuk_ui
  {

    class RipnetUkButtonComponent : public button::Button, public Component
    {
    public:
      RipnetUkButtonComponent(); // Neeed as it seems to construct one in main.cpp if we AUTO_LOAD this which we seem to have to... <------ G is a noob!
      RipnetUkButtonComponent(const std::string &name, std::function<void()> on_click);

    private:
       std::function<void()> _on_click;

    protected:
      void press_action() override;
    };
  } // namespace ripnetuk_ui
} // namespace esphome
