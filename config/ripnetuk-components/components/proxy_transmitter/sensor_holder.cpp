#include "sensor_holder.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace proxy_transmitter
  {
    SensorHolder::SensorHolder(sensor::Sensor *sensor)
    {
      sensor_ = sensor;
      sensor_->add_on_state_callback([this](float state)
                                     { this->on_state_callback(state); });
    }

    void SensorHolder::on_state_callback(float state)
    {
      ESP_LOGD(TAG->get_tag(), "Sensor[%d] state callback %f", sensor_index, state);
      has_state_ = true;
      state_ = state;
    }

    void SensorHolder::update()
    {
      has_state_ = false;

      PollingComponent *as_polling_component = dynamic_cast<PollingComponent *>(sensor_);
      if (as_polling_component)
      {
        ESP_LOGD(TAG->get_tag(), "Sensor[%d] calling update as PollingComponent", sensor_index);
        as_polling_component->update();
      }
    }
  } // namespace proxy_transmitter
} // namespace esphome
