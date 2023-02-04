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
      // Need to do this before setting up ESPNow as it switches wifi off...
      peer_receiver_->peer_setup(); // this kills the wifi component
    }

    void ProxyTransmitterComponent::loop()
    {
      // Setup ESPNow stuff here as we know WiFi component has finished messing with the wifi
      if (!loop_has_run_)
      {
        // This seems to be needed to have ESPNow and WiFi working together
        WiFi.mode(WIFI_AP_STA);
        WiFi.channel(peer_receiver_->get_espnow_channel());

        setup_espnow();

        peer_receiver_->espnow_add_peer();
      }

      peer_receiver_->loop();
      loop_has_run_ = true;
    }
  } // namespace proxy_transmitter
} // namespace esphome
