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
            case PS_PEER_ADDED:
                output->append("Peer Added");
                break;
            default:
                output->append("!! UNKONWN PEER STATE TYPE !!");
            }
        }
    } // namespace proxy_base
} // namespace esphome

// output->append("(PING)" + std::to_string(message->message_type));
