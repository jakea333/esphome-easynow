#include "proxy_receiver.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome
{
  namespace proxy_receiver
  {

    static const char *TAG = "proxy_receiver";

    void ProxyReceiverComponent::loop()
    {
      ESP_LOGD(TAG, "Time %d", millis());
    }

    float ProxyReceiverComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

  } // namespace proxy_receiver
} // namespace esphome
