#pragma once

#include "esphome/core/component.h"

#ifdef USE_ESP_IDF
#include <esp_heap_caps.h>
#include <esp_system.h>
#endif

#ifdef USE_ARDUINO
#include <Esp.h>
#endif

namespace esphome
{
  namespace debug
  {

    class MemoryComponent : public PollingComponent
    {
    private:
      uint32_t previous_value_ = 0;

    public:
      void update() override;
      float get_setup_priority() const override;
    };

  } // namespace debug
} // namespace esphome
