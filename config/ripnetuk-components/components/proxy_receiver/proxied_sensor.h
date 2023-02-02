#pragma once

#include "esphome/core/component.h"
#include "../proxy_base/log_tag.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome
{
  namespace proxy_receiver
  {
    class ProxiedSensorComponent : public sensor::Sensor, public Component
    {
    private:
    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("ProxiedSensorComponent");

    public:
      const char *proxy_id;
    };

  } // namespace proxy_receiver
} // namespace esphome
