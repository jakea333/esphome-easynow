#include "proxy_receiver.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/peer_mac_address.h"
#include "proxied_sensor.h"
#include "esphome/core/application.h"
#include "ota_switch.h"
#include <string>

namespace esphome
{
  namespace proxy_receiver
  {

    void ProxyReceiverComponent::add_peer_transmitter(PeerTransmitter *peer_transmitter)
    {
      OTASwitchComponent *new_ota_switch = new OTASwitchComponent();

      std::string *switch_name = new std::string();
      switch_name->append(peer_transmitter->get_name());
      switch_name->append(" OTA Mode");

      new_ota_switch->set_name(*switch_name);
      App.register_switch(new_ota_switch);
      App.register_component(new_ota_switch);

      peer_transmitter->ota_switch = new_ota_switch;

      peer_transmitters_->push_back(peer_transmitter);
    }

    void ProxyReceiverComponent::setup()
    {
      // This seems to be needed to have ESPNow and WiFi working together
      WiFi.mode(WIFI_AP_STA);
      
      setup_espnow();
      
      ESP_LOGD(TAG->get_tag(), "Adding peers...");
      for (int i = 0; i < peer_transmitters_->size(); i++)
      {
        peer_transmitters_->at(i)->espnow_add_peer();
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
