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
                output->append("PING");
                break;
            default:
                output->append("!! UNKONWN MESSAGE TYPE !!");
            }
        }
    } // namespace proxy_base
} // namespace esphome

// output->append("(PING)" + std::to_string(message->message_type));
