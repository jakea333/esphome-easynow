#include "peer_mac_address.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include <WiFi.h>

namespace esphome
{
  namespace proxy_base
  {
    void PeerMacAddress::set_from_uint64_t(uint64_t value)
    {
      const uint8_t *bytes = reinterpret_cast<const uint8_t *>(&value);
      // Its little endian on our ESPs so cant just use as is..
      for (int i = 0; i < ESP_NOW_ETH_ALEN; i++)
      {
        as_uint8_t_array[i] = bytes[ESP_NOW_ETH_ALEN - 1 - i];
      }
      update_as_string();
    }

    void PeerMacAddress::set_from_uint8_t_array(const uint8_t *value)
    {
      memcpy(&as_uint8_t_array, value, sizeof(as_uint8_t_array));
      update_as_string();
    }

    bool PeerMacAddress::mac_address_equals(PeerMacAddress *other)
    {
      for (int i = 0; i < ESP_NOW_ETH_ALEN; i++)
      {
        if (as_uint8_t_array[i] != other->as_uint8_t_array[i])
          return false;
      }
      return true;
    }

    void PeerMacAddress::update_as_string()
    {
      if (as_string != NULL)
      {
        free(as_string);
      }
      as_string = (char *)malloc(3 * ESP_NOW_ETH_ALEN);
      sprintf(as_string, "%02X:%02X:%02X:%02X:%02X:%02X", as_uint8_t_array[0], as_uint8_t_array[1], as_uint8_t_array[2], as_uint8_t_array[3], as_uint8_t_array[4], as_uint8_t_array[5]);
    }

  } // namespace proxy_base
} // namespace esphome