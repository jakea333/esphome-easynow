#include "peer_transmitter.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"
#include <WiFi.h>

namespace esphome
{
  namespace proxy_receiver
  {
    void PeerTransmitter::handle_received_proxy_message(proxy_base::proxy_message *message)
    {
      if (message->message_type == proxy_base::T_TO_R_CHECKIN)
      {
        // Send a response
        proxy_base::proxy_message msg;
        msg.message_type = proxy_base::R_TO_T_CHECKIN_RESP;
        send_proxy_message(&msg);
      }

      if (message->message_type == proxy_base::T_TO_R_SEND_SENSOR_STATE)
      {
        // Send a response
        proxy_base::proxy_message send_msg;
        send_msg.message_type = proxy_base::R_TO_T_SEND_SENDOR_STATE_REPONSE;
        memcpy(send_msg.send_sensor_state_response.proxy_id, message->send_sensor_state.proxy_id, PROXY_ID_MAX_LENGTH);
        
        send_proxy_message(&send_msg);
      }
    }

    void PeerTransmitter::loop()
    {
      if (get_state() == proxy_base::PS_READY)
      {
        // Just waiting for incoming messages.
        return;
      }

      ESP_LOGD(TAG->get_tag(), "Unexpected state in loop - %d ", get_state());
    }
  } // namespace proxy_receiver
} // namespace esphome
