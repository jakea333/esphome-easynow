#pragma once

#include "esphome/core/component.h"
#include "../proxy_base/proxy_base.h"
#include "peer_receiver.h"
#include "../proxy_base/log_tag.h"
#include <vector>
#include "esphome/components/sensor/sensor.h"

namespace esphome
{
  namespace proxy_transmitter
  {

    class ProxyTransmitterComponent : public proxy_base::ProxyBaseComponent
    {
    private:
    protected:
      PeerReceiver *peer_receiver_ = new PeerReceiver();

    public:
      vector<sensor::Sensor *> sensors = new vector<sensor::Sensor>();
      void loop() override;
      void setup() override;
      void set_espnow_channel(int channel) { espnow_channel_ = channel; }
      void set_receiver_mac_address(uint64_t mac_address) { peer_receiver_->mac_address.set_from_uint64_t(mac_address); };
      void add_sensor(sensor::Sensor *sensor) { sensors->push_back(sensor); };

    } // namespace proxy_transmitter
  }   // namespace esphome
