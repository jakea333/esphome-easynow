#pragma once

#include "../proxy_base/peer_base.h"
#include "../proxy_base/log_tag.h"
#include "../proxy_base/proxy_messages.h"
#include <vector>
#include "proxied_sensor.h"
#include "ota_switch.h"

namespace esphome
{
  namespace proxy_receiver
  {
    class PeerTransmitter : public proxy_base::PeerBase
    {
    private:
      void update_proxied_sensor(proxy_base::proxy_message *message);

    public:
      std::vector<ProxiedSensorComponent *> *proxied_sensors = new std::vector<ProxiedSensorComponent *>();
      OTASwitchComponent *ota_switch;

      void loop();

    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("PeerTransmitter");
      void handle_received_proxy_message(proxy_base::proxy_message *message);
    };

  } // namespace proxy_receiver
} // namespace esphome
