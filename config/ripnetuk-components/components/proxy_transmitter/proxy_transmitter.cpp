#include "proxy_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/proxy_messages.h"
#include <esp_now.h>

#define TEST_MESSAGE_PERIOD 5000

uint8_t receiverAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
esp_now_peer_info_t peerInfo;

namespace esphome
{
  namespace proxy_transmitter
  {
    static const char *TAG = "proxy_transmitter";

    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
    {
      ESP_LOGD(TAG, "Last Packet Send Status:");
      ESP_LOGD(TAG, (status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail"));
    }

    void ProxyTransmitterComponent::setup()
    {
      ESP_LOGD(TAG, "Setting WiFi mode");
      WiFi.mode(WIFI_AP_STA);
      ESP_LOGD(TAG, "WiFi mode set");
      if (esp_now_init() != ESP_OK)
      {
        ESP_LOGD(TAG, "Error initializing ESP-NOW");
        return;
      }
      ESP_LOGD(TAG, "ESP-NOW Initialized");

      esp_now_register_send_cb(OnDataSent);
      memcpy(peerInfo.peer_addr, receiverAddress, 6);
      peerInfo.channel = 11;
      peerInfo.encrypt = false;

      if (esp_now_add_peer(&peerInfo) != ESP_OK)
      {
        ESP_LOGD(TAG, "Failed to add peer");
        return;
        ESP_LOGD(TAG, "Peer Added");
      }
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

        esp_err_t result = esp_now_send(receiverAddress, (uint8_t *)&msg, sizeof(msg));

        if (result == ESP_OK)
        {
          Serial.println("Sent with success");
        }
        else
        {
          Serial.println("Error sending the data");
        }
      }
    }
  } // namespace proxy_transmitter
} // namespace esphome
