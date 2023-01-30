#include "proxy_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "../proxy_base/proxy_payload.h"

namespace esphome
{
  namespace proxy_transmitter
  {
    static const char *TAG = "proxy_transmitter";

    void ProxyTransmitterComponent::loop()
    {
      proxy_base::ProxyPayload pl;
      ESP_LOGD(TAG, "Time %d magic %d", millis(), pl.get_magic_number());
    }

    float ProxyTransmitterComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

  } // namespace proxy_transmitter
} // namespace esphome
