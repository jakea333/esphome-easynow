#pragma once
#include <string>

namespace esphome
{
    namespace proxy_base
    {
        enum proxy_message_type
        {
            T_TO_R_CHECKIN = 20,
            R_TO_T_CHECKIN_RESP = 30,
            T_TO_R_SEND_SENSOR_STATE = 40,
            R_TO_T_SEND_SENDOR_STATE_REPONSE = 50
        };

        typedef struct proxy_message_send_sensor_state
        {
            int sensor_index;
            float state;
        } proxy_message_send_sensor_state;

        typedef struct proxy_message_send_sensor_state_response
        {
            int sensor_index;
        } proxy_message_send_sensor_state_response;

        typedef struct proxy_message
        {
            proxy_message_type message_type;
            int time_stamp;
            union
            {
                proxy_message_send_sensor_state send_sensor_state;
                proxy_message_send_sensor_state_response send_sensor_state_response;
            };
        } proxy_message_header;

        void describe_proxy_message(std::string *output, proxy_message *message);
    } // namespace proxy_base
} // namespace esphome
