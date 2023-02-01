#include "proxy_messages.h"

namespace esphome
{
    namespace proxy_base
    {
        void describe_proxy_message(std::string *output, proxy_message *message)
        {
            output->append("TYPE " + std::to_string(message->message_type));
        }
    } // namespace proxy_base
} // namespace esphome
