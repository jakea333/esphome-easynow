#pragma once

#include "esphome/core/component.h"
#include "../proxy_base/proxy_base.h"
#include "peer_transmitter.h"
#include <vector>
#include "../proxy_base/log_tag.h"

namespace esphome
{
  namespace proxy_receiver
  {
    class ProxyReceiverComponent : public proxy_base::ProxyBaseComponent
    {
    private:
      std::vector<PeerTransmitter *> *peer_transmitters_ = new std::vector<PeerTransmitter *>();

    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("ProxyReceiverComponent");
      void handle_received_proxy_message(const uint8_t *mac_addr, proxy_base::proxy_message *message) override;

    public:
      void loop() override;
      void setup() override;
      void set_espnow_channel(int channel) { espnow_channel_ = channel; }
      void add_transmitter(uint64_t mac_address, int testinput);
    };

  } // namespace proxy_receiver
} // namespace esphome
