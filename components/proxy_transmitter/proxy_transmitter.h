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
      int loop_run_ = false;
    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("PeerReceiver");
      PeerReceiver *peer_receiver_ = new PeerReceiver();

    public:
      void set_peer_receiver(PeerReceiver *peer_receiver) { peer_receiver_ = peer_receiver; }
      // Hardware priority so we can kill off the wifi component before it starts...
      // float get_setup_priority() const override { return setup_priority::HARDWARE; }
      float get_setup_priority() const override { return setup_priority::WIFI; }
      void loop() override;
      void setup() override;
    };
  } // namespace proxy_transmitter
} // namespace esphome
