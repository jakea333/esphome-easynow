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

    public:
      void loop() override;
      void setup() override;
      void add_peer_transmitter(PeerTransmitter *peer_transmitter);
    };

  } // namespace proxy_receiver
} // namespace esphome
