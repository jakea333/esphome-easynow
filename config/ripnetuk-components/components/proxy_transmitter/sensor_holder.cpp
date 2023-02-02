#include "sensor_holder.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace proxy_transmitter
  {
    SensorHolder::SensorHolder(sensor::Sensor *sensor, const char *proxy_id)
    {
      sensor_ = sensor;
      this->proxy_id = proxy_id;
      sensor_->add_on_state_callback([this](float state)
                                     { this->on_state_callback(state); });
    }

    void SensorHolder::on_state_callback(float state)
    {
      //ESP_LOGD(TAG->get_tag(), "Sensor[%d] state callback %f", sensor_index, state);
      has_state = true;
      this->state = state;
    }
  } // namespace proxy_transmitter
} // namespace esphome
