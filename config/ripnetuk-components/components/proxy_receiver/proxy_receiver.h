#pragma once

#include "esphome/core/component.h"
#include "../proxy_base/proxy_base.h"
#include "transmitter_info.h"
#include <vector>

namespace esphome
{
  namespace proxy_receiver
  {
    class ProxyReceiverComponent : public proxy_base::ProxyBaseComponent
    {
    private:
      std::vector<TransmitterInfo *> *transmitters_ = new std::vector<TransmitterInfo *>();

    protected:
      int espnow_channel_;
      void handle_received_proxy_message(const uint8_t *mac_addr, proxy_base::proxy_message *message) override;

    public:
      void loop() override;
      void setup() override;
      void set_espnow_channel(int channel) { espnow_channel_ = channel; }
      void add_transmitter(uint64_t mac_address, int testinput);
    };

  } // namespace proxy_receiver
} // namespace esphome
