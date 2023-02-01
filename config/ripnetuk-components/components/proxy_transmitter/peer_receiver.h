#pragma once
#include "../proxy_base/peer_base.h"
#include "../proxy_base/log_tag.h"

namespace esphome
{
  namespace proxy_transmitter
  {
    class PeerReceiver : public proxy_base::PeerBase
    {
    protected:
      proxy_base::LogTag *TAG = new proxy_base::LogTag("PeerReceiver");
    };

  } // namespace proxy_receiver
} // namespace esphome
