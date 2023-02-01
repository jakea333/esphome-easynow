#include "peer_receiver.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>

namespace esphome
{
  namespace proxy_transmitter
  {
    void PeerReceiver::handle_received_proxy_message(proxy_base::proxy_message *message)
    {
    }

    void PeerReceiver::loop()
    {
      if (get_state() == proxy_base::PS_PEER_ADDED)
      {
        // Want to send a 
      }
    }

  } // namespace proxy_receiver
} // namespace esphome
