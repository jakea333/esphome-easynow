#include "proxy_messages.h"

namespace esphome
{
    namespace proxy_base
    {
        void describe_proxy_message(std::string *output, proxy_message *message)
        {
            switch (message->message_type)
            {
            case PING:
                output->append("Ping");
                break;
            case T_TO_R_CHECKIN:
                output->append("T to R Check in");
                break;
            case R_TO_T_CHECKIN_RESP:
                output->append("R to C Check in response");
                break;
            default:
                output->append("!! UNKONWN MESSAGE TYPE !!");
            }
        }
    } // namespace proxy_base
} // namespace esphome

// output->append("(PING)" + std::to_string(message->message_type));
