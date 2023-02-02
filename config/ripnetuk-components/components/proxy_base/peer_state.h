#pragma once
#include <string>

namespace esphome
{
    namespace proxy_base
    {
        enum peer_state
        {
            PS_UNSET = 5,
            PS_READY = 10,
            PS_T_AWAIT_R_TO_T_CHECKIN_RESP = 20,
            PS_T_READING_SENSORS = 25,
            PS_T_SENDING_STATES = 30,
            PS_T_AWAIT_R_TO_T_SEND_STATE_RESP = 40
        };

        void describe_peer_state(std::string *output, peer_state state);
    } // namespace proxy_base
} // namespace esphome
