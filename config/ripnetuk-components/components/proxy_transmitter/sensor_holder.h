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
      bool has_state_ = false;
      float state_ = NAN;
      void on_state_callback(float state);
    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("SensorHolder");

    public:
      int sensor_index {0};
      SensorHolder(sensor::Sensor *sensor);
      bool get_has_state() { return has_state_; }
      bool get_state() { return state_; }
      void update();
    };
  } // namespace proxy_transmitter
} // namespace esphome
