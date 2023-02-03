#pragma once

#include "../proxy_base/peer_base.h"
#include "../proxy_base/log_tag.h"
#include "../proxy_base/proxy_messages.h"
#include <vector>
#include "esphome/components/sensor/sensor.h"
#include "sensor_holder.h"

namespace esphome
{
  namespace proxy_transmitter
  {
    class PeerReceiver : public proxy_base::PeerBase
    {
    public:
      void add_sensor(sensor::Sensor *sensor, const char *proxy_id) { sensors_->push_back(new SensorHolder(sensor, proxy_id)); };
      void set_deep_sleep_length(int deep_sleep_length) { deep_sleep_length_ = deep_sleep_length; }
      void peer_workflow_loop();

    private:
      std::vector<SensorHolder *> *sensors_ = new std::vector<SensorHolder *>();
      int deep_sleep_length_; // in ms
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
