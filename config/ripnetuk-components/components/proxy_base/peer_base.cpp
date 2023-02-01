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
        ESP_LOGD(TAG->get_tag(), "Failed to add peer %s", mac_address.as_string);
        return false;
        ESP_LOGD(TAG->get_tag(), "Peer Added %s", mac_address.as_string);
      }
      global_peer_list_->push_back(this);

      last_state_change_millis_ = millis();
      set_state(PS_READY);

      return true;
    }

    bool PeerBase::send_proxy_message(proxy_message *message)
    {
      message->time_stamp = millis();

      std::string desc;
      describe_proxy_message(&desc, message);

      esp_err_t result = esp_now_send(peer_info_.peer_addr, (uint8_t *)message, sizeof(*message));

      if (result != ESP_OK)
      {
        ESP_LOGD(TAG->get_tag(), "> Data Send to %s failed (%s)", mac_address.as_string, desc.c_str());
        return false;
      }
      ESP_LOGD(TAG->get_tag(), "> Data Send to %s success (%s)", mac_address.as_string, desc.c_str());
      return true;
    }

    PeerBase *PeerBase::find_peer_in_global_peer_list(PeerMacAddress *peer)
    {
      for (int i = 0; i < global_peer_list_->size(); i++)
      {
        if (global_peer_list_->at(i)->mac_address.mac_address_equals(peer))
          return global_peer_list_->at(i);
      }

      return NULL;
    }

    void PeerBase::call_on_data_send_callback(const uint8_t *mac_addr, esp_now_send_status_t status)
    {
      PeerMacAddress callback_peer;
      callback_peer.set_from_uint8_t_array(mac_addr);

      PeerBase *peer = find_peer_in_global_peer_list(&callback_peer);
      if (peer == NULL)
      {
        ESP_LOGD("PeerBaseComponent", "Received unexpected DataSent callback from unknown peer %s", callback_peer.as_string);
        return;
      }
      peer->on_data_send_callback(status);
    }

    void PeerBase::call_on_data_recv_callback(const uint8_t *mac_addr, const uint8_t *incomingData, int len)
    {

      PeerMacAddress callback_peer;

      callback_peer.set_from_uint8_t_array(mac_addr);

      PeerBase *peer = find_peer_in_global_peer_list(&callback_peer);
      if (peer == NULL)
      {
        ESP_LOGD("PeerBaseComponent", "Received unexpected DataRecv callback from unknown peer %s", callback_peer.as_string);
        return;
      }
      peer->on_data_recv_callback(incomingData, len);
    }

    void PeerBase::on_data_send_callback(esp_now_send_status_t status)
    {
      ESP_LOGD(TAG->get_tag(), "> Data Send to %s - Status - %s", mac_address.as_string, (status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail"));
    }

    void PeerBase::on_data_recv_callback(const uint8_t *incomingData, int len)
    {
      proxy_message message;
      memcpy(&message, incomingData, sizeof(message));

      std::string desc;
      describe_proxy_message(&desc, &message);

      ESP_LOGD(TAG->get_tag(), "< Data Recv from %s (%s)", mac_address.as_string, desc.c_str());
    }

    peer_state PeerBase::get_state()
    {
      return state_;
    }

    void PeerBase::set_state(peer_state state)
    {
      std::string old_desc;
      describe_peer_state(&old_desc, state_);

      state_ = state;

      std::string new_desc;
      describe_peer_state(&new_desc, state_);

      ESP_LOGD(TAG->get_tag(), "State change on %s from %s to %s after %f3s", mac_address.as_string, old_desc.c_str(), new_desc.c_str(), (millis() - last_state_change_millis_) / 1000.0);

      last_state_change_millis_ = millis();
    }
  } // namespace proxy_base
} // namespace esphome
