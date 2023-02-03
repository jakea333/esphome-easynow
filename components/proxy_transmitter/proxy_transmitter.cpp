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
      // This seems to be needed to have ESPNow and WiFi working together
      WiFi.mode(WIFI_AP_STA);

      setup_espnow();

      // // Turn off wifi

      // ESP_LOGD(TAG->get_tag(), "Disconnecting WiFi");
      // //        wifi_->clear_sta();
      // WiFi.disconnect();
      // ESP_LOGD(TAG->get_tag(), "WiFi disconnected");

      peer_receiver_->espnow_add_peer();
    }

    void ProxyTransmitterComponent::loop()
    {
      peer_receiver_->loop();
    }
  } // namespace proxy_transmitter
} // namespace esphome
