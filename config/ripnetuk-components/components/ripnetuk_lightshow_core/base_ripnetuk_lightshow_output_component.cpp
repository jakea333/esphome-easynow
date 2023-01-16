#include "base_ripnetuk_lightshow_output_component.h"
#include "esphome/core/log.h"
#include "esphome.h"

namespace esphome
{
  namespace ripnetuk_lightshow_core
  {
    static const char *TAG = "base_ripnetuk_lightshow_output";

    float BaseRipnetUkLightshowOutputComponent::get_setup_priority() const
    {
      return setup_priority::HARDWARE;
    }
    
    void BaseRipnetUkLightshowOutputComponent::output_frame(ripnetuk_lightshow_core::Frame *frame)
    {
    }
  }
}
