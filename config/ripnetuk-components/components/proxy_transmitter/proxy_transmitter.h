#pragma once

#include "esphome/core/component.h"
#include "../proxy_base/proxy_base.h"
#include "peer_receiver.h"
#include "../proxy_base/log_tag.h"

namespace esphome
{
  namespace proxy_transmitter
  {

    class ProxyTransmitterComponent : public proxy_base::ProxyBaseComponent
    {
    private:
      int last_testmessage_millis{0};

    protected:
      PeerReceiver *peer_receiver_ = new PeerReceiver();
      void handle_received_proxy_message(const uint8_t *mac_addr, proxy_base::proxy_message *message) override;

    public:
      void loop() override;
      void setup() override;
      void set_espnow_channel(int channel) { espnow_channel_ = channel; }
      void set_receiver_mac_address(uint64_t mac_address) { peer_receiver_->mac_address = mac_address; };
    };

  } // namespace proxy_transmitter
} // namespace esphome
