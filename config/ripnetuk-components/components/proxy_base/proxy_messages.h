#pragma once
#include <string>

namespace esphome
{
    namespace proxy_base
    {
        enum proxy_message_type
        {
            PING = 10,
            T_TO_R_CHECKIN = 20,
            R_TO_T_CHECKIN_RESP = 30
        };

        typedef struct proxy_message_ping
        {
        } proxy_message_ping;

        typedef struct proxy_message
        {
            proxy_message_type message_type;
            int time_stamp;
            union
            {
                proxy_message_ping ping;
            };
        } proxy_message_header;

        void describe_proxy_message(std::string *output, proxy_message *message);
    } // namespace proxy_base
} // namespace esphome
