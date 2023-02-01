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
      if (get_state() == proxy_base::PS_T_AWAIT_R_TO_T_CHECKIN_RESP)
      {
        if (message->message_type == proxy_base::R_TO_T_CHECKIN_RESP)
        {
          set_state(proxy_base::PS_READY);
        }
        return;
      }

      ESP_LOGD(TAG->get_tag(), "Unexpected message type %d when in state %d", message->message_type, get_state());
    }

    void PeerReceiver::loop()
    {
      ESP_LOGD(TAG->get_tag(), "LOOP");
      if (get_state() == proxy_base::PS_READY)
      {
        // Want to send a checkin
        proxy_base::proxy_message msg;
        msg.message_type = proxy_base::T_TO_R_CHECKIN;
        send_proxy_message(&msg);
        // Set state to awaiting R_TO_T_CHECKIN_RESP
        set_state(proxy_base::PS_T_AWAIT_R_TO_T_CHECKIN_RESP);
      }
      return;

      ESP_LOGD(TAG->get_tag(), "Unexpected state in loop - %d ", get_state());
    }
  } // namespace proxy_receiver
} // namespace esphome
