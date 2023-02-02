#include "proxy_messages.h"

namespace esphome
{
    namespace proxy_base
    {
        void describe_proxy_message(std::string *output, proxy_message *message)
        {
            switch (message->message_type)
            {
            case T_TO_R_CHECKIN:
                output->append("T to R Check in");
                break;
            case R_TO_T_CHECKIN_RESP:
                output->append("R to C Check in response");
                break;
            case T_TO_R_SEND_SENSOR_STATE:
                output->append("T to R Send Sensor[%d] State - %f", message->send_sensor_state.sensor_index, message->send_sensor_state.state);
                break;
            default:
                output->append("!! UNKONWN MESSAGE TYPE !!");
            }
        }
    } // namespace proxy_base
} // namespace esphome

// output->append("(PING)" + std::to_string(message->message_type));
