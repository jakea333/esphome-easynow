#include "ripnetuk_neopixel_component.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace ripnetuk_neopixel
  {
    static const char *TAG = "ripnetuk_neopixel";

    void RipnetUkNeopixelComponent::loop()
    {
     // ESP_LOGD(TAG, "neopixel Heap Size: %u bytes", free_heap);
    }

    float RipnetUkNeopixelComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

  } // namespace debug
} // namespace esphome
