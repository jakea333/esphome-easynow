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
      ESP_LOGD(TAG->get_tag(), "Add peer %s", mac_address.as_string);

      memcpy(&peer_info_.peer_addr, &mac_address.as_uint8_t_array, sizeof(peer_info_.peer_addr));

      // peer_info_.peer_addr = mac_address.as_uint8_t_array;
      peer_info_.channel = espnow_channel;
      peer_info_.encrypt = false;

      if (esp_now_add_peer(&peer_info_) != ESP_OK)
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
      esp_err_t result = esp_now_send(peer_info_.peer_addr, (uint8_t *)message, sizeof(*message));

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
      PeerMacAddress callback_peer;
      callback_peer.set_from_uint8_t_array(mac_addr);

      for (int i = 0; i < global_peer_list_->size(); i++)
      {
        if (global_peer_list_->at(i)->mac_address.mac_address_equals(&callback_peer))
          return global_peer_list_->at(i);
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
