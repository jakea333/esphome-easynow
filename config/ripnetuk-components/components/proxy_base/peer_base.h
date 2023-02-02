#pragma once

#include "esphome/core/hal.h"
#include <esp_now.h>
#include "proxy_messages.h"
#include "log_tag.h"
#include <vector>
#include "peer_mac_address.h"
#include "peer_state.h"

namespace esphome
{
  namespace proxy_base
  {

    class PeerBase
    {
    private:
      esp_now_peer_info_t peer_info_;
      peer_state state_ = PS_UNSET;
      // This is a hack since I cannot find a way of passing a method pointer to the ESPNow callbacks...
      static std::vector<PeerBase *> *global_peer_list_;
      void on_data_send_callback(esp_now_send_status_t status);
      void on_data_recv_callback(const uint8_t *incomingData, int len);
      static PeerBase *find_peer_in_global_peer_list(PeerMacAddress *peer);

    public:
      PeerMacAddress mac_address;
      const char *name;
      bool add_espnow_peer(int espnow_channel);
      // Callbacks from ESPNow
      static void call_on_data_send_callback(const uint8_t *mac_addr, esp_now_send_status_t status);
      static void call_on_data_recv_callback(const uint8_t *mac_addr, const uint8_t *incomingData, int len);
      virtual void loop() = 0;

    protected:
      LogTag *TAG = new LogTag("PeerBase");

      int last_state_change_millis_;
      void set_state(peer_state state);
      peer_state get_state();
      void reset_state(const char *reason);
      bool send_proxy_message(proxy_message *message);
      virtual void handle_received_proxy_message(proxy_message *message) = 0;
    };
  } // namespace proxy_base
} // namespace esphome
