#include "proxy_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/proxy_messages.h"

#define TEST_MESSAGE_PERIOD 5000

// uint8_t peer_address[] = {0x34, 0x86, 0x5D, 0xFD, 0x84, 0x58};

namespace esphome
{
  namespace proxy_transmitter
  {
    static const char *TAG = "ProxyTransmitterComponent";

    void ProxyTransmitterComponent::setup()
    {
      setup_espnow(11);
      add_espnow_peer(receiver_->mac_address);
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

        send_proxy_message(&msg);
      }
    }

    void ProxyTransmitterComponent::handle_received_proxy_message(const uint8_t *mac_addr, proxy_base::proxy_message *message)
    {
      ESP_LOGD(TAG, "HANDLE RECEIVED MESSAGE");
    }
  } // namespace proxy_transmitter
} // namespace esphome
