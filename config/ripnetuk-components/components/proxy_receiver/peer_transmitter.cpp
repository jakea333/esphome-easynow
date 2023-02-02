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
        proxy_base::proxy_message send_msg;
        send_msg.message_type = proxy_base::R_TO_T_CHECKIN_RESP;
        send_proxy_message(&send_msg);
      }

      if (message->message_type == proxy_base::T_TO_R_SEND_SENSOR_STATE)
      {
        // Update local state...
        update_proxied_sensor(message);
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

    void PeerTransmitter::update_proxied_sensor(proxy_base::proxy_message *message)
    {
      // Need to find the sensor with our proxy_id
      ProxiedSensorComponent *proxied_sensor = NULL;
      for (int i = 0; i < proxied_sensors->size(); i++)
      {
        if (strcmp(message->send_sensor_state.proxy_id, proxied_sensors->at(i)->proxy_id))
        {
          proxied_sensor = proxied_sensors->at(i);
          break;
        }
      }

      if (!proxied_sensor)
      {
        ESP_LOGD(TAG->get_tag(), "Received sensor state from %s (%s) with proxy_id of %s but no such proxied sensor exists.", name, mac_address.as_string, message->send_sensor_state.proxy_id);
        return;
      }
      float state = message->send_sensor_state.state;
      ESP_LOGD(TAG->get_tag(), "^^Publish state from %s (%s) with proxy_id of %s - state is %f", name, mac_address.as_string, message->send_sensor_state.proxy_id, state);
      proxied_sensor->publish_state(state);
    }
  } // namespace proxy_receiver
} // namespace esphome
