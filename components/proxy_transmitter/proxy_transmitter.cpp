#include "proxy_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/proxy_messages.h"
#include "../proxy_base/esp_result_decoder.h"

#define TEST_MESSAGE_PERIOD 5000

// void PeerReceiver::peer_setup()
// {
//   // ESP_LOGD(TAG->get_tag(), "Killing Wifi Component");
//   // wifi_->clear_sta();
// }

namespace esphome
{
  namespace proxy_transmitter
  {
    void ProxyTransmitterComponent::setup()
    {
      // This runs before wifi component starts up...
      get_wifi()->mark_failed(); // To kill it
    }

    void ProxyTransmitterComponent::first_loop()
    {
      // // This seems to be needed to have ESPNow and WiFi working together
      // wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
      // // cfg.nvs_enable = false;
      // proxy_base::ESPResultDecoder::check_esp_result(esp_netif_init(), "esp_netif_init");
      // proxy_base::ESPResultDecoder::check_esp_result(esp_wifi_init(&cfg), "esp_wifi_init");

      // proxy_base::ESPResultDecoder::check_esp_result(WiFi.mode(WIFI_AP), "Set wifi mode");
      int channel = peer_receiver_->get_espnow_channel();
      // // ESP_LOGD(TAG->get_tag(), "Setting WiFi channels to %d / none", channel);
      // // proxy_base::ESPResultDecoder::check_esp_result(WiFi.channel(channel), "WiFi.channel");

      // proxy_base::ESPResultDecoder::check_esp_result(WiFi.softAP("dummyssid", "dummypassword", channel), "WiFi.softAP");

      // proxy_base::ESPResultDecoder::check_esp_result(WiFi.mode(WIFI_STA), "WiFi.mode");
      // proxy_base::ESPResultDecoder::check_esp_result(WiFi.disconnect(), "WiFi.disconnect");

      // get_wifi()->setup();

      setup_espnow();

      peer_receiver_->espnow_add_peer();
      //proxy_base::ESPResultDecoder::check_esp_result(esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE), "esp_wifi_set_channel");
    }

    void ProxyTransmitterComponent::loop()
    {
      if (!loop_run_)
      {
        loop_run_ = true;
        // ESP_LOGD(TAG->get_tag(), "************************************************************************** FIRST LOOP START");
        first_loop();
        // ESP_LOGD(TAG->get_tag(), "************************************************************************** FIRST LOOP END");
        return;
      }

      peer_receiver_->loop();
    }
  } // namespace proxy_transmitter
} // namespace esphome

// // Turn off wifi

// ESP_LOGD(TAG->get_tag(), "Disconnecting WiFi");
// //        wifi_->clear_sta();
// WiFi.disconnect();
// ESP_LOGD(TAG->get_tag(), "WiFi disconnected");

// void ProxyTransmitterComponent::setup()
// {
//   // Need to do this before setting up ESPNow as it switches wifi off...
//   // peer_receiver_->peer_setup(); // this kills the wifi component's ap and sets
//   ESP_LOGD(TAG->get_tag(), "a*****************************************");
//   setup_espnow();
//   ESP_LOGD(TAG->get_tag(), "b*****************************************");

//   peer_receiver_->espnow_add_peer();
//   ESP_LOGD(TAG->get_tag(), "c*****************************************");
// }
// loop_count_++;
// // Allow a few loops for the wifi component to do its thing
// // if (loop_count_ < 50)
// // {
// //   return;
// // }

// // Setup ESPNow stuff here as we know WiFi component has finished messing with the wifi
// if (loop_count_ == 1)
// {
//   ESP_LOGD(TAG->get_tag(), "***************************************** 1 LOOP ***************************888");

//   // ESP_LOGD(TAG->get_tag(), "Init wifi");
//   // wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//   // esp_err_t init_result = esp_wifi_init(&cfg);
//   // if (init_result == ESP_OK)
//   // {
//   //   ESP_LOGD(TAG->get_tag(), "Init OK");
//   // }
//   // else
//   // {
//   //   ESP_LOGD(TAG->get_tag(), "Error %d %s init wifi", init_result, decode_esp_result(init_result));
//   // }

//   int channel = peer_receiver_->get_espnow_channel();
//   // ESP_LOGD(TAG->get_tag(), "Setting WiFi channels to %d / none", channel);
//   // esp_err_t channel_result = WiFi.channel(channel);
//   // if (channel_result == ESP_OK)
//   // {
//   //   ESP_LOGD(TAG->get_tag(), "Set channel OK");
//   // }
//   // else
//   // {
//   //   ESP_LOGD(TAG->get_tag(), "Error %d %s setting channel", channel_result, decode_esp_result(channel_result));
//   // }
//   // esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);

//   // ESP_LOGD(TAG->get_tag(), "Setting WiFi mode to STA", channel);

//   // esp_err_t mode_result = WiFi.mode(WIFI_AP);
//   // if (mode_result == ESP_OK)
//   // {
//   //   ESP_LOGD(TAG->get_tag(), "Set mode OK");
//   // }
//   // else
//   // {
//   //   ESP_LOGD(TAG->get_tag(), "Error %d %s setting mode", mode_result, decode_esp_result(mode_result));
//   // }

//   // setup_espnow();

//   // peer_receiver_->espnow_add_peer();
//   return;
// }