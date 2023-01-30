#include "proxy_receiver.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include "../proxy_base/proxy_payload.h"

namespace esphome
{
  namespace proxy_receiver
  {

    static const char *TAG = "proxy_receiver";

    void ProxyReceiverComponent::loop()
    {
      proxy_base::ProxyPayload pl;

      ESP_LOGD(TAG, "Time %d magic %d", millis(), pl.get_magic_number());
    }

    float ProxyReceiverComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

  } // namespace proxy_receiver
} // namespace esphome
