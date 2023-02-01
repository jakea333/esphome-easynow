#include "proxy_receiver.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/log_tag.h"

namespace esphome
{
  namespace proxy_receiver
  {

    proxy_base::LogTag *TAG = new proxy_base::LogTag("ProxyReceiverComponent");

    void ProxyReceiverComponent::add_transmitter(uint64_t mac_address, int testinput)
    {
      PeerTransmitter *peer_transmitter = new PeerTransmitter();
      peer_transmitter->mac_address = mac_address;
      peer_transmitters_->push_back(peer_transmitter);
    }

    void ProxyReceiverComponent::setup()
    {
      setup_espnow(espnow_channel_);
      ESP_LOGD(TAG->get_tag(), "Adding peers...");
      for (int i = 0; i < peer_transmitters_->size(); i++)
      {
        peer_transmitters_->at(i)->add_espnow_peer(espnow_channel_);
      }
    }

    void ProxyReceiverComponent::loop()
    {
      proxy_base::ProxyBaseComponent::loop();
    }

    void ProxyReceiverComponent::handle_received_proxy_message(const uint8_t *mac_addr, proxy_base::proxy_message *message)
    {
      ESP_LOGD(TAG->get_tag(), "HANDLE RECEIVED MESSAGE");
    }
  } // namespace proxy_receiver
} // namespace esphome
