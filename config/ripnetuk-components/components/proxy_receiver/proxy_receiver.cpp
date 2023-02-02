#include "proxy_receiver.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/peer_mac_address.h"
#include "proxied_sensor.h"
#include "esphome/core/application.h"

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

    void ProxyReceiverComponent::add_proxied_sensor(uint64_t mac_address, const char *proxy_id, const char *name)
    {
      // Find peer transmitter with this mac address...
      PeerTransmitter *peer_transmitter = NULL;
      proxy_base::PeerMacAddress peer_mac_address;
      peer_mac_address.set_from_uint64_t(mac_address);

      for (int i = 0; i < peer_transmitters_->size(); i++)
      {
        if (peer_transmitters_->at(i)->mac_address.mac_address_equals(&peer_mac_address))
        {
          peer_transmitter = peer_transmitters_->at(i);
        }
      }

      if (peer_transmitter == NULL)
      {
        ESP_LOGD(TAG->get_tag(), "Error - Attempt to add a proxied sensor to transmitter with mac address %s but we dont have such a transmitter", peer_mac_address.as_string);
        return;
      }

      ProxiedSensorComponent *new_proxied_sensor = new ProxiedSensorComponent();
      new_proxied_sensor->set_name(name);
      new_proxied_sensor->proxy_id = proxy_id;

      App.register_sensor(new_proxied_sensor);
      App.register_component(new_proxied_sensor);

      peer_transmitter->proxied_sensors->push_back(new_proxied_sensor);
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
