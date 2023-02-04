#include "proxy_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/proxy_messages.h"
#include "../proxy_base/decode_esp_error.h"

#define TEST_MESSAGE_PERIOD 5000

namespace esphome
{
  namespace proxy_transmitter
  {
    void ProxyTransmitterComponent::setup()
    {
      // Need to do this before setting up ESPNow as it switches wifi off...
      peer_receiver_->peer_setup(); // this kills the wifi component's ap and sets
    }

    void ProxyTransmitterComponent::loop()
    {
      loop_count_++;
      // Allow a few loops for the wifi component to do its thing
      if (loop_count_ < 50)
      {
        return;
      }

      // Setup ESPNow stuff here as we know WiFi component has finished messing with the wifi
      if (loop_count_ == 50)
      {
        ESP_LOGD(TAG->get_tag(), "***************************************** 50th LOOP ***************************888");

        ESP_LOGD(TAG->get_tag(), "Init wifi");
        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        esp_err_t init_result = esp_wifi_init(&cfg);
        if (init_result == ESP_OK)
        {
          ESP_LOGD(TAG->get_tag(), "Init OK");
        }
        else
        {
          ESP_LOGD(TAG->get_tag(), "Error %d %s init wifi", init_result, decode_esp_error(init_result));
        }


        int channel = peer_receiver_->get_espnow_channel();
        ESP_LOGD(TAG->get_tag(), "Setting WiFi channel to %d", channel);
        esp_err_t channel_result = WiFi.channel(channel);
        if (channel_result == ESP_OK)
        {
          ESP_LOGD(TAG->get_tag(), "Set channel OK");
        }
        else
        {
          ESP_LOGD(TAG->get_tag(), "Error %d %s setting channel", channel_result, decode_esp_error(channel_result));
        }

        ESP_LOGD(TAG->get_tag(), "Setting WiFi mode to STA", channel);

        esp_err_t mode_result = WiFi.mode(WIFI_AP);
        if (mode_result == ESP_OK)
        {
          ESP_LOGD(TAG->get_tag(), "Set mode OK");
        }
        else
        {
          ESP_LOGD(TAG->get_tag(), "Error %d %s setting mode", mode_result, decode_esp_error(mode_result));
        }

        setup_espnow();

        peer_receiver_->espnow_add_peer();
        return;
      }

      peer_receiver_->loop();
    }
  } // namespace proxy_transmitter
} // namespace esphome
