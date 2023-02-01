#include "proxy_base.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "esphome/core/application.h"
#include <stdio.h>
#include "log_tag.h"

#define PROXY_LOG_PERIOD 60000

namespace esphome
{
  namespace proxy_base
  {
    // This is a hack since I cannot find a way of passing a method pointer to the ESPNow callbacks...
    std::vector<ProxyBaseComponent *> *ProxyBaseComponent::callback_component_list_ = new std::vector<ProxyBaseComponent *>();

    ProxyBaseComponent::ProxyBaseComponent()
    {
      callback_component_list_->push_back(this);
    }

    void ProxyBaseComponent::ProxyBaseComponent::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
    {
      //ESP_LOGD(TAG->get_tag(), "%s Last Packet Send Status:", App.get_name().c_str());
      //ESP_LOGD(TAG->get_tag(), (status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail"));
    }

    void ProxyBaseComponent::OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
    {
      proxy_message message;
      memcpy(&message, incomingData, sizeof(message));
      //ESP_LOGD(TAG->get_tag(), "Bytes received: %d messge_type %d", len, message.message_type);
      for (int i = 0; i < callback_component_list_->size(); i++)
      {
        callback_component_list_->at(i)->handle_received_proxy_message(mac_addr, &message);
      }
    }

    float ProxyBaseComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

    bool ProxyBaseComponent::setup_espnow(int channel)
    {
      espnow_is_setup_ = false;

      ESP_LOGD(TAG->get_tag(), "Setting WiFi mode");
      WiFi.mode(WIFI_AP_STA);
      ESP_LOGD(TAG->get_tag(), "WiFi mode set");
      if (esp_now_init() != ESP_OK)
      {
        ESP_LOGD(TAG->get_tag(), "Error initializing ESP-NOW");
        return false;
      }
      ESP_LOGD(TAG->get_tag(), "ESP-NOW Initialized");

      esp_now_register_send_cb(OnDataSent);
      esp_now_register_recv_cb(OnDataRecv);

      espnow_is_setup_ = true;

      return true;
    }
  } // namespace proxy_base
} // namespace esphome
