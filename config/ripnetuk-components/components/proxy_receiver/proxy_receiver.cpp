#include "proxy_receiver.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>

namespace esphome
{
  namespace proxy_receiver
  {

    void ProxyReceiverComponent::add_transmitter(uint64_t mac_address, const char *name)
    {
      PeerTransmitter *peer_transmitter = new PeerTransmitter();
      peer_transmitter->name = name;
      peer_transmitter->mac_address.set_from_uint64_t(mac_address);
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
      for (int i = 0; i < peer_transmitters_->size(); i++)
      {
        peer_transmitters_->at(i)->loop();
      }
    }

  } // namespace proxy_receiver
} // namespace esphome
