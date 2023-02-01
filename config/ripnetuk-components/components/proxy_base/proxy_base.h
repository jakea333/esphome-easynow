#pragma once

#include "esphome/core/component.h"
#include <esp_now.h>
#include "proxy_messages.h"
#include "peer_base.h"

namespace esphome
{
  namespace proxy_base
  {

    class ProxyBaseComponent : public Component
    {
    private:


    public:
      float get_setup_priority() const override;

    protected:
      LogTag *TAG = new LogTag("ProxyBaseComponent");
      int espnow_channel_;
      bool espnow_is_setup_{false};
      bool setup_espnow(int channel);
      virtual void handle_received_proxy_message(const uint8_t *mac_addr, proxy_message *message) = 0;
    };

  } // namespace proxy_base
} // namespace esphome
