#pragma once

#include "esphome/core/component.h"
#include <esp_now.h>
#include "proxy_messages.h"
#include "peer_base.h"

namespace esphome
{
  namespace proxy_base
  {

    class ProxyBaseComponent : public Component
    {
    private:
    public:
    protected:
      LogTag *TAG = new LogTag("ProxyBaseComponent");

      bool espnow_is_setup_{false};
      bool setup_espnow();
    };

  } // namespace proxy_base
} // namespace esphome
