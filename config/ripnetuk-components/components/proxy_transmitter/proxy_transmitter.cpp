#include "proxy_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/proxy_messages.h"
#include "../proxy_base/log_tag.h"

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
      proxy_base::ProxyBaseComponent::loop();
      if ((millis() - last_testmessage_millis) > TEST_MESSAGE_PERIOD)
      {
        last_testmessage_millis = millis();

        proxy_base::proxy_message msg;
        msg.message_type = proxy_base::PING;
        msg.time_stamp = millis();

        peer_receiver_->send_proxy_message(&msg);
      }
    }

    void ProxyTransmitterComponent::handle_received_proxy_message(const uint8_t *mac_addr, proxy_base::proxy_message *message)
    {
      ESP_LOGD(TAG->get_tag(), "HANDLE RECEIVED MESSAGE");
    }
  } // namespace proxy_transmitter
} // namespace esphome
