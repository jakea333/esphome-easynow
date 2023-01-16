#pragma once

#include "esphome/core/component.h"

namespace esphome
{
  namespace ripnetuk_lightshow_core
  {
    class BaseRipnetUkLightshowInputComponent : public Component
    {
    public:
      float get_setup_priority() const override;

    private:
    };

  } // namespace ripnetuk_lightshow_core
} // namespace esphome
