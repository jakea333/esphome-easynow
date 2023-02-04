#include "proxy_base.h"
#include "esphome/core/log.h"

#include <WiFi.h>
#include "log_tag.h"
#include "decode_esp_result.h"

#define PROXY_LOG_PERIOD 60000

namespace esphome
{
  namespace proxy_base
  {
    bool ProxyBaseComponent::setup_espnow()
    {
      espnow_is_setup_ = false;
      check_esp_result(esp_now_init(), "esp_now_init");

      check_esp_result(esp_now_register_send_cb(PeerBase::call_on_data_send_callback), "esp_now_register_send_cb");
      check_esp_result(esp_now_register_recv_cb(PeerBase::call_on_data_recv_callback), "esp_now_register_recv_cb");

      espnow_is_setup_ = true;

      return true;
    }
  } // namespace proxy_base
} // namespace esphome
