#include "proxy_receiver.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>

uint8_t peer_address[] = {0x34, 0x86, 0x5D, 0xFC, 0x5E, 0xE0};

namespace esphome
{
  namespace proxy_receiver
  {

    static const char *TAG = "proxy_receiver";

    void ProxyReceiverComponent::add_transmitter(uint64_t mac_address, int testinput)
    {
    }
    
    void ProxyReceiverComponent::setup()
    {
      setup_espnow(11);
      add_espnow_peer(peer_address);
    }

    void ProxyReceiverComponent::loop()
    {
      proxy_base::ProxyBaseComponent::loop();
    }

    void ProxyReceiverComponent::handle_received_proxy_message(const uint8_t *mac_addr, proxy_base::proxy_message *message)
    {
      ESP_LOGD(TAG, "HANDLE RECEIVED MESSAGE");
    }
  } // namespace proxy_receiver
} // namespace esphome
