#include "proxy_base.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>

#define PROXY_LOG_PERIOD 2000

namespace esphome
{
  namespace proxy_base
  {
    static const char *TAG = "proxy_base";

    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
    {
      ESP_LOGD(TAG, "Last Packet Send Status:");
      ESP_LOGD(TAG, (status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail"));
    }

    void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
    {
      proxy_message message;
      memcpy(&message, incomingData, sizeof(message));
      ESP_LOGD(TAG, "Bytes received: %d messge_type %d", len, message.message_type);
    }

    void ProxyBaseComponent::loop()
    {
      if ((millis() - last_log_millis_) > PROXY_LOG_PERIOD)
      {
        last_log_millis_ = millis();
        ESP_LOGD(TAG, "%s Time %d ", WiFi.macAddress().c_str(), millis());
      }
    }

    float ProxyBaseComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

    bool ProxyBaseComponent::setup_espnow(int channel, uint8_t peer_address[])
    {
      espnow_is_setup_ = false;

      ESP_LOGD(TAG, "Setting WiFi mode");
      WiFi.mode(WIFI_AP_STA);
      ESP_LOGD(TAG, "WiFi mode set");
      if (esp_now_init() != ESP_OK)
      {
        ESP_LOGD(TAG, "Error initializing ESP-NOW");
        return false;
      }
      ESP_LOGD(TAG, "ESP-NOW Initialized");

      esp_now_register_send_cb(OnDataSent);
      esp_now_register_recv_cb(OnDataRecv);
      
      memcpy(peerInfo.peer_addr, peer_address, 6);
      peerInfo.channel = 11;
      peerInfo.encrypt = false;

      if (esp_now_add_peer(&peerInfo) != ESP_OK)
      {
        ESP_LOGD(TAG, "Failed to add peer");
        return false;
        ESP_LOGD(TAG, "Peer Added");
      }
      espnow_is_setup_ = true;
      return true;
    }

    bool ProxyBaseComponent::send_proxy_message(proxy_message *message)
    {
      if (!espnow_is_setup_)
      {
        ESP_LOGD(TAG, "Send Proxy Message Called when ESPNow if not setup.");
        return false;
      }
      esp_err_t result = esp_now_send(peerInfo.peer_addr, (uint8_t *)message, sizeof(*message));

      if (result != ESP_OK)
      {
        ESP_LOGD(TAG, "Send failed");
        return false;
      }
      ESP_LOGD(TAG, "Sent with success");
      return true;
    }
  } // namespace proxy_base
} // namespace esphome
