#include "proxy_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome
{
  namespace proxy_transmitter
  {
    static const char *TAG = "proxy_transmitter";

    void ProxyTransmitterComponent::loop()
    {
      ESP_LOGD(TAG, "Transmitter Time %d", millis());
    }

    float ProxyTransmitterComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

  } // namespace proxy_transmitter
} // namespace esphome
