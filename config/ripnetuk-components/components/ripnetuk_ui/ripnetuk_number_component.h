#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/number/number.h"

namespace esphome
{
  namespace ripnetuk_ui
  {

    class RipnetUkNumberComponent : public number::Number, public Component
    {
    public:
      RipnetUkNumberComponent(); // Neeed as it seems to construct one in main.cpp if we AUTO_LOAD this which we seem to have to... <------ G is a noob!
      RipnetUkNumberComponent(const std::string &name, std::function<void(float state)> on_change);
      void setup() override;
      float get_setup_priority() const override;
    protected:
      void control(float state) override;
    private:
      std::function<void(float state)> _on_change;
      float _deviceSideState;
    };
  } // namespace ripnetuk_ui
} // namespace esphome
