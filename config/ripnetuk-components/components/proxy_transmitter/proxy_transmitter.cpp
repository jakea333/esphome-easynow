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
    proxy_base::LogTag *TAG = new proxy_base::LogTag("ProxyTransmitterComponent");

    void ProxyTransmitterComponent::setup()
    {
      setup_espnow(espnow_channel_);
      peer_receiver_->add_espnow_peer(espnow_channel_);
    }

    void ProxyTransmitterComponent::loop()
    {
      peer_receiver_->loop();
    }
  } // namespace proxy_transmitter
} // namespace esphome
