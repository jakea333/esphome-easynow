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
      std::vector<SensorHolder *> *sensors = new std::vector<SensorHolder *>();
      void set_peer_receiver(PeerReceiver *peer_receiver) { peer_receiver_=peer_receiver;}
      void loop() override;
      void setup() override;
      // void set_espnow_channel(int channel) { espnow_channel_ = channel; }
      // void set_receiver(uint64_t mac_address, const char *name)
      // {
      //   peer_receiver_->mac_address.set_from_uint64_t(mac_address);
      //   peer_receiver_->name = name;
      // }
      void add_sensor(sensor::Sensor *sensor, const char *proxy_id) { sensors->push_back(new SensorHolder(sensor, proxy_id)); };
    };
  } // namespace proxy_transmitter
} // namespace esphome
