#pragma once

#include "esphome/core/hal.h"

namespace esphome
{
  namespace proxy_base
  {
    class PeerInfoBase
    {
    private:
    public:
      uint64_t mac_address;

    protected:
    };
  } // namespace proxy_base
} // namespace esphome
