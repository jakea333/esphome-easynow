#include "proxy_base.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "esphome/core/application.h"
#include <stdio.h>

#define PROXY_LOG_PERIOD 60000

namespace esphome
{
  namespace proxy_base
  {
    char *tag_ = NULL;
    char *get_tag()
    {
      if (tag_ == NULL)
      {
        tag_ = (char *)malloc(100);
        sprintf(tag_, "[%s] ProxyBaseComponent", App.get_name().c_str());
      }
      return tag_;
    }

    std::vector<ProxyBaseComponent *> *ProxyBaseComponent::callback_component_list_ = new std::vector<ProxyBaseComponent *>();

    ProxyBaseComponent::ProxyBaseComponent()
    {
      callback_component_list_->push_back(this);
    }

    void ProxyBaseComponent::ProxyBaseComponent::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
    {
      ESP_LOGD(get_tag(), "%s Last Packet Send Status:", App.get_name().c_str());
      ESP_LOGD(get_tag(), (status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail"));
    }

    void ProxyBaseComponent::OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
    {
      proxy_message message;
      memcpy(&message, incomingData, sizeof(message));
      ESP_LOGD(get_tag(), "Bytes received: %d messge_type %d", len, message.message_type);
      for (int i = 0; i < callback_component_list_->size(); i++)
      {
        callback_component_list_->at(i)->handle_received_proxy_message(mac_addr, &message);
      }
    }

    void ProxyBaseComponent::loop()
    {
      if ((millis() - last_log_millis_) > PROXY_LOG_PERIOD)
      {
        last_log_millis_ = millis();
        ESP_LOGD(get_tag(), "%s Time %d ", WiFi.macAddress().c_str(), millis());
      }
    }

    float ProxyBaseComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

    bool ProxyBaseComponent::setup_espnow(int channel)
    {
      espnow_is_setup_ = false;

      ESP_LOGD(get_tag(), "Setting WiFi mode");
      WiFi.mode(WIFI_AP_STA);
      ESP_LOGD(get_tag(), "WiFi mode set");
      if (esp_now_init() != ESP_OK)
      {
        ESP_LOGD(get_tag(), "Error initializing ESP-NOW");
        return false;
      }
      ESP_LOGD(get_tag(), "ESP-NOW Initialized");

      esp_now_register_send_cb(OnDataSent);
      esp_now_register_recv_cb(OnDataRecv);

      espnow_is_setup_ = true;

      return true;
    }

    bool ProxyBaseComponent::add_espnow_peer(uint64_t peer_mac_address)
    {
      const uint8_t *peer_mac_address_bytes = reinterpret_cast<const uint8_t *>(&peer_mac_address);

      // Its little endian on our ESPs so cant just use as is..
      for (int i = 0; i < 6; i++)
      {
        peerInfo.peer_addr[i] = peer_mac_address_bytes[5 - i];
      }
      // memcpy(peerInfo.peer_addr, peer_mac_address, 6);

      ESP_LOGD(get_tag(), "Add peer %02X:%02X:%02X:%02X:%02X:%02X", peerInfo.peer_addr[0], peerInfo.peer_addr[1], peerInfo.peer_addr[2], peerInfo.peer_addr[3], peerInfo.peer_addr[4], peerInfo.peer_addr[5]);
      
      peerInfo.channel = 11;
      peerInfo.encrypt = false;

      if (esp_now_add_peer(&peerInfo) != ESP_OK)
      {
        ESP_LOGD(get_tag(), "Failed to add peer");
        return false;
        ESP_LOGD(get_tag(), "Peer Added");
      }

      return true;
    }

    bool ProxyBaseComponent::send_proxy_message(proxy_message *message)
    {
      if (!espnow_is_setup_)
      {
        ESP_LOGD(get_tag(), "Send Proxy Message Called when ESPNow if not setup.");
        return false;
      }
      esp_err_t result = esp_now_send(peerInfo.peer_addr, (uint8_t *)message, sizeof(*message));

      if (result != ESP_OK)
      {
        ESP_LOGD(get_tag(), "Send failed");
        return false;
      }
      ESP_LOGD(get_tag(), "Sent with success");
      return true;
    }
  } // namespace proxy_base
} // namespace esphome
