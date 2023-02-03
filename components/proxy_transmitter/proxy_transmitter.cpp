#include "proxy_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/proxy_messages.h"

#define TEST_MESSAGE_PERIOD 5000

namespace esphome
{
  namespace proxy_transmitter
  {
    void ProxyTransmitterComponent::setup()
    {
      setup_espnow();
      // Give each sensor an index for logging
      for (int i = 0; i < sensors->size(); i++)
      {
        sensors->at(i)->sensor_index = i;
      }
      peer_receiver_->sensors = sensors;
      peer_receiver_->espnow_add_peer();
    }

    void ProxyTransmitterComponent::loop()
    {
      peer_receiver_->loop();
    }
  } // namespace proxy_transmitter
} // namespace esphome
