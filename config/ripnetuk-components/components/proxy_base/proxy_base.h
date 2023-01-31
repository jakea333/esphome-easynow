#pragma once

#include "esphome/core/component.h"
#include <esp_now.h>
#include "proxy_messages.h"

namespace esphome
{
  namespace proxy_base
  {

    class ProxyBaseComponent : public Component
    {
    private:
      int last_log_millis_{0};
      esp_now_peer_info_t peerInfo;
    public:
      float get_setup_priority() const override;
      void loop() override;

    protected:
      bool espnow_is_setup_{false};
      bool setup_espnow(int channel, uint8_t receiverAddress[]);
      bool send_proxy_message(proxy_message* message);
    };

  } // namespace proxy_base
} // namespace esphome
