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

    PeerBase *PeerBase::find_peer_in_global_peer_list(const uint8_t *mac_addr)
    {

      for (int i_peer = 0; i_peer < global_peer_list_->size(); i_peer++)
      {
        PeerBase *peer = global_peer_list_->at(i_peer);
        const uint8_t *peer_mac_address_bytes = reinterpret_cast<const uint8_t *>(&peer->mac_address);
        bool is_match = true;
        for (int i = 0; i < 6; i++)
        {
          if (mac_addr[i] != peer_mac_address_bytes[5 - i])
          {
            is_match = false;
            break;
          }
        }
        if (is_match)
        {
          return peer;
        }
      }
      return NULL;
    }

    void PeerBase::call_on_data_send_callback(const uint8_t *mac_addr, esp_now_send_status_t status)
    {
      PeerBase *peer = find_peer_in_global_peer_list(mac_addr);
      if (peer == NULL)
      {
        ESP_LOGD("PeerBaseComponent", "Received unexpected DataSent callback from unknown peer -  %02X:%02X:%02X:%02X:%02X:%02X", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        return;
      }
      peer->on_data_send_callback(status);
    }

    void PeerBase::call_on_data_recv_callback(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
    {
      PeerBase *peer = find_peer_in_global_peer_list(mac_addr);
      if (peer == NULL)
      {
        ESP_LOGD("PeerBaseComponent", "Received unexpected DataRecv callback from unknown peer -  %02X:%02X:%02X:%02X:%02X:%02X", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        return;
      }
      peer->on_data_recv_callback(incomingData, len);
    }

    void PeerBase::on_data_send_callback(esp_now_send_status_t status)
    {
      ESP_LOGD(TAG->get_tag(), "> Data Send - Status - %s", (status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail"));
    }

    void PeerBase::on_data_recv_callback(const uint8_t *incomingData, int len)
    {
      proxy_message message;
      memcpy(&message, incomingData, sizeof(message));
      ESP_LOGD(TAG->get_tag(), "< Data Recv");
    }

  } // namespace proxy_base
} // namespace esphome
