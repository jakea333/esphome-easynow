#include "peer_base.h"
#include "esphome/core/log.h"
#include <string.h>
// #include <WiFi.h>

namespace esphome
{
  namespace proxy_base
  {
    std::vector<PeerBase *> *PeerBase::global_peer_list_ = new std::vector<PeerBase *>();

    bool PeerBase::add_espnow_peer(int espnow_channel)
    {
      const uint8_t *peer_mac_address_bytes = reinterpret_cast<const uint8_t *>(&mac_address);

      // Its little endian on our ESPs so cant just use as is..
      for (int i = 0; i < 6; i++)
      {
        peerInfo.peer_addr[i] = peer_mac_address_bytes[5 - i];
      }
      // memcpy(peerInfo.peer_addr, peer_mac_address, 6);

      ESP_LOGD(TAG->get_tag(), "Add peer %02X:%02X:%02X:%02X:%02X:%02X", peerInfo.peer_addr[0], peerInfo.peer_addr[1], peerInfo.peer_addr[2], peerInfo.peer_addr[3], peerInfo.peer_addr[4], peerInfo.peer_addr[5]);

      peerInfo.channel = espnow_channel;
      peerInfo.encrypt = false;

      if (esp_now_add_peer(&peerInfo) != ESP_OK)
      {
        ESP_LOGD(TAG->get_tag(), "Failed to add peer");
        return false;
        ESP_LOGD(TAG->get_tag(), "Peer Added");
      }
      global_peer_list_->push_back(this);
      return true;
    }

    bool PeerBase::send_proxy_message(proxy_message *message) 
    {
      esp_err_t result = esp_now_send(peerInfo.peer_addr, (uint8_t *)message, sizeof(*message));

      if (result != ESP_OK)
      {
        ESP_LOGD(TAG->get_tag(), "Send failed");
        return false;
      }
      ESP_LOGD(TAG->get_tag(), "Sent with success");
      return true;
    }

    void PeerBase::OnDataSentCallback(const uint8_t *mac_addr, esp_now_send_status_t status)
    {
      // ESP_LOGD(TAG->get_tag(), "%s Last Packet Send Status:", App.get_name().c_str());
      // ESP_LOGD(TAG->get_tag(), (status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail"));
    }

    void PeerBase::OnDataRecvCallback(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
    {
      proxy_message message;
      memcpy(&message, incomingData, sizeof(message));
      // ESP_LOGD(TAG->get_tag(), "Bytes received: %d messge_type %d", len, message.message_type);
      for (int i = 0; i < global_peer_list_->size(); i++)
      {
        // callback_component_list_->at(i)->handle_received_proxy_message(mac_addr, &message);
      }
    }
  } // namespace proxy_base
} // namespace esphome
