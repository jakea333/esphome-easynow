#pragma once

#include "../proxy_base/peer_base.h"
#include "../proxy_base/log_tag.h"
#include "../proxy_base/proxy_messages.h"
#include <vector>
#include "esphome/components/sensor/sensor.h"
#include "sensor_holder.h"
#include "esphome/components/ota/ota_component.h"

namespace esphome
{
  namespace proxy_transmitter
  {
    class PeerReceiver : public proxy_base::PeerBase
    {
    public:
      ota::OTAComponent *ota;
      std::vector<SensorHolder *> *sensors = new std::vector<SensorHolder *>();
      void peer_workflow_loop();

    private:
      void start_sensor_reads();
      SensorHolder *get_first_unsent_sensor();
      void enter_ota_mode();
      void go_to_sleep();

    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("PeerReceiver");
      void handle_received_proxy_message(proxy_base::proxy_message *message);
    };

  } // namespace proxy_receiver
} // namespace esphome
