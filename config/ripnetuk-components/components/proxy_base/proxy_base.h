#pragma once

#include "esphome/core/component.h"
#include <esp_now.h>
#include "proxy_messages.h"
#include "peer_base.h"
#include <vector>

namespace esphome
{
  namespace proxy_base
  {

    class ProxyBaseComponent : public Component
    {
    private:
      static std::vector<ProxyBaseComponent *> *callback_component_list_;
      static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
      static void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len);

    public:
      ProxyBaseComponent();
      float get_setup_priority() const override;

    protected:
      int espnow_channel_;
      bool espnow_is_setup_{false};
      bool setup_espnow(int channel);
      virtual void handle_received_proxy_message(const uint8_t *mac_addr, proxy_message *message) = 0;
    };

  } // namespace proxy_base
} // namespace esphome
