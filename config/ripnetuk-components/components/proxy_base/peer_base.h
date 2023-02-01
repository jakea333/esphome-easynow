#pragma once

#include "esphome/core/hal.h"
#include <esp_now.h>
#include "proxy_messages.h"
#include "log_tag.h"

namespace esphome
{
  namespace proxy_base
  {
    class PeerBase
    {
    private:
      esp_now_peer_info_t peerInfo;

    public:
      uint64_t mac_address;
      bool add_espnow_peer(int espnow_channel);
      bool send_proxy_message(proxy_message *message);
    protected:
      LogTag *TAG = new LogTag("PeerBase");
    };
  } // namespace proxy_base
} // namespace esphome
