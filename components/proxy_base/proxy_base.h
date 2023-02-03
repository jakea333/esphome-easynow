#pragma once

#include "esphome/core/component.h"
#include "esphome/components/wifi/wifi_component.h"
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
      float get_setup_priority() const override;
      void set_wifi(wifi::WiFiComponent *wifi) { wifi_ = wifi; }

    protected:
      LogTag *TAG = new LogTag("ProxyBaseComponent");

      wifi::WiFiComponent *wifi_;
      bool espnow_is_setup_{false};
      bool setup_espnow();
      virtual bool get_enable_wifi() = 0;
    };

  } // namespace proxy_base
} // namespace esphome
