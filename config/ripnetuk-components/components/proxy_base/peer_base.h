#pragma once

#include "esphome/core/hal.h"
#include <esp_now.h>
#include "proxy_messages.h"
#include "log_tag.h"
#include <vector>

namespace esphome
{
  namespace proxy_base
  {
    class PeerBase
    {
    private:
      esp_now_peer_info_t peerInfo;
      // This is a hack since I cannot find a way of passing a method pointer to the ESPNow callbacks...
      static std::vector<PeerBase *> *global_peer_list_;

    public:
      uint64_t mac_address;
      bool add_espnow_peer(int espnow_channel);
      bool send_proxy_message(proxy_message *message);
      // Callbacks from ESPNow
      static void OnDataSentCallback(const uint8_t *mac_addr, esp_now_send_status_t status);
      static void OnDataRecvCallback(const uint8_t *mac_addr, const uint8_t *incomingData, int len);

    protected:
      LogTag *TAG = new LogTag("PeerBase");
    };
  } // namespace proxy_base
} // namespace esphome
