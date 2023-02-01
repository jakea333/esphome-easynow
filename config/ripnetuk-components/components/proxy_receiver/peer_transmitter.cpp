#include "peer_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>
#include "../proxy_base/log_tag.h"

// uint8_t peer_address[] = {0x34, 0x86, 0x5D, 0xFC, 0x5E, 0xE0};

namespace esphome
{
  namespace proxy_receiver
  {
    proxy_base::LogTag *TAG = new proxy_base::LogTag("PeerTransmitter");
  } // namespace proxy_receiver
} // namespace esphome
