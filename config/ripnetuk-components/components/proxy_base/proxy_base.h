#pragma once

#include "esphome/core/component.h"
#include <esp_now.h>
#include "proxy_messages.h"
#include <vector>

namespace esphome
{
  namespace proxy_base
  {

    class ProxyBaseComponent : public Component
    {
    private:
      int last_log_millis_{0};
      esp_now_peer_info_t peerInfo;
      static std::vector<ProxyBaseComponent *> *callback_component_list_;
      static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
      static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

    public:
      ProxyBaseComponent();
      float get_setup_priority() const override;
      void loop() override;

    protected:
      bool espnow_is_setup_{false};
      bool setup_espnow(int channel, uint8_t receiverAddress[]);
      bool send_proxy_message(proxy_message *message);
      virtual void handle_received_proxy_message(proxy_message *message) = 0;
    };

  } // namespace proxy_base
} // namespace esphome
