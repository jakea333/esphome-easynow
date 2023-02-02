#include "peer_state.h"

namespace esphome
{
    namespace proxy_base
    {
        void describe_peer_state(std::string *output, peer_state state)
        {
            switch (state)
            {
            case PS_UNSET:
                output->append("Unset");
                break;
            case PS_READY:
                output->append("Ready");
                break;
            case PS_T_AWAIT_R_TO_T_CHECKIN_RESP:
                output->append("(T) Await R to T Check in Response");
                break;
            case PS_T_READING_SENSORS:
                output->append("(T) Reading Sensors");
                break;
            case PS_T_SENDING_STATES:
                output->append("(T) Sending States");
                break;
            default:
                output->append("!! UNKONWN PEER STATE TYPE !!");
            }
        }
    } // namespace proxy_base
} // namespace esphome

// output->append("(PING)" + std::to_string(message->message_type));
