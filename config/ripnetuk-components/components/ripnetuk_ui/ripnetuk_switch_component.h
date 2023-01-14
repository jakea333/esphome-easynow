#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/switch/switch.h"

namespace esphome
{
  namespace ripnetuk_ui
  {

    class RipnetUkSwitchComponent : public switch_::Switch, public Component
    {
    public:
      RipnetUkSwitchComponent(); // Neeed as it seems to construct one in main.cpp if we AUTO_LOAD this which we seem to have to... <------ G is a noob!
      RipnetUkSwitchComponent(const std::string &name);
      void setup() override;
      float get_setup_priority() const override;
    protected:
      bool assumed_state() override;
      void write_state(bool state) override;
    private:
      bool _deviceSideState;
    };
  } // namespace ripnetuk_ui
} // namespace esphome
