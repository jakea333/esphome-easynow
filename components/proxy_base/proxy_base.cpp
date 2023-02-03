#include "proxy_base.h"
#include "esphome/core/log.h"

#include <WiFi.h>
#include "log_tag.h"

#define PROXY_LOG_PERIOD 60000

namespace esphome
{
  namespace proxy_base
  {
    float ProxyBaseComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
      int x;
    }

    bool ProxyBaseComponent::setup_espnow()
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

      esp_now_register_send_cb(PeerBase::call_on_data_send_callback);
      esp_now_register_recv_cb(PeerBase::call_on_data_recv_callback);

      espnow_is_setup_ = true;

      return true;
    }
  } // namespace proxy_base
} // namespace esphome
