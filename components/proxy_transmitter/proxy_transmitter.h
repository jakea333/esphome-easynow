#pragma once

#include "esphome/core/component.h"
#include "../proxy_base/proxy_base.h"
#include "peer_receiver.h"
#include "../proxy_base/log_tag.h"
#include <vector>
#include "sensor_holder.h"
#include "esphome/components/ota/ota_component.h"

namespace esphome
{
  namespace proxy_transmitter
  {
    class ProxyTransmitterComponent : public proxy_base::ProxyBaseComponent
    {
    private:
    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("PeerReceiver");
      PeerReceiver *peer_receiver_ = new PeerReceiver();

    public:

      void set_peer_receiver(PeerReceiver *peer_receiver) { peer_receiver_ = peer_receiver; }
      void loop() override;
      void setup() override;
    };
  } // namespace proxy_transmitter
} // namespace esphome
