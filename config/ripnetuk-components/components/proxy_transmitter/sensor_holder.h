#pragma once

#include "../proxy_base/log_tag.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome
{
  namespace proxy_transmitter
  {
    class SensorHolder
    {
    private:
      sensor::Sensor *sensor_;
      void on_state_callback(float state);

    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("SensorHolder");

    public:
      SensorHolder(sensor::Sensor *sensor);
      int sensor_index{0};
      bool is_sent = false;
      bool has_state = false;
      float state = NAN;
    };
  } // namespace proxy_transmitter
} // namespace esphome
