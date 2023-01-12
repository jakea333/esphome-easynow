#include "ripnetuk_neopixel_component.h"
#include "esphome/core/log.h"

#ifdef USE_ESP_IDF
#include <esp_heap_caps.h>
#include <esp_system.h>
#endif

#ifdef USE_ARDUINO
#include <Esp.h>
#endif

namespace esphome
{
  namespace ripnetuk_neopixel
  {

    static const char *TAG = "memory";

    void RipnetUkNeopixelComponent::update()
    {
#ifdef USE_ARDUINO
      uint32_t free_heap = ESP.getFreeHeap(); // NOLINT(readability-static-accessed-through-instance)
#elif defined(USE_ESP_IDF)
      uint32_t free_heap = heap_caps_get_free_size(MALLOC_CAP_INTERNAL);
#endif

      ESP_LOGD(TAG, "yyyyFree Heap Size: %u bytes", free_heap);
    }

    float RipnetUkNeopixelComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

  } // namespace debug
} // namespace esphome
