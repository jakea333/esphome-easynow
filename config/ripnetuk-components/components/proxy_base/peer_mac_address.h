#pragma once

#include "esphome/core/hal.h"
#include <esp_now.h>

namespace esphome
{
  namespace proxy_base
  {
    class PeerMacAddress
    {
    private:
    public:
      char * as_string;
      uint8_t as_uint8_t_array[ESP_NOW_ETH_ALEN];
      void set_from_uint64_t(uint64_t value);
      void set_from_uint8_t_array(const uint8_t *value);
      bool mac_address_equals(PeerMacAddress *other);
    protected:
    };
  } // namespace proxy_base
} // namespace esphome
