#include "proxy_base.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>

#define PROXY_LOG_PERIOD 2000

namespace esphome
{
  namespace proxy_base
  {
    static const char *TAG = "proxy_base";

    void ProxyBaseComponent::loop()
    {
      if ((millis() - last_log_millis_) > PROXY_LOG_PERIOD)
      {
        last_log_millis_ = millis();
        ESP_LOGD(TAG, "%s Time %d ", WiFi.macAddress().c_str(), millis());
      }
    }

    float ProxyBaseComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

  } // namespace proxy_base
} // namespace esphome
