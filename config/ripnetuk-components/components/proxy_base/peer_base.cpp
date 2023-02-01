#include "peer_base.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace proxy_base
  {
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
  } // namespace proxy_base
} // namespace esphome
