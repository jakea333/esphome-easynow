#pragma once

#include "../proxy_base/peer_base.h"
#include "../proxy_base/log_tag.h"
#include "../proxy_base/proxy_messages.h"

namespace esphome
{
  namespace proxy_receiver
  {
    class PeerTransmitter : public proxy_base::PeerBase
    {
    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("PeerTransmitter");
      void handle_received_proxy_message(proxy_base::proxy_message *message);
      void loop();
    };

  } // namespace proxy_receiver
} // namespace esphome
