#pragma once

#include "esphome/core/component.h"
#include "frame.h"

namespace esphome
{
  namespace ripnetuk_lightshow_core
  {
    class BaseRipnetUkLightshowInputComponent //: public Component
    {
    public:
      // float get_setup_priority() const override;
      virtual void input_frame(ripnetuk_lightshow_core::Frame *frame, ripnetuk_lightshow_core::Frame *output_frame_so_far) = 0;
    private:
    };

  } // namespace ripnetuk_lightshow_core
} // namespace esphome
