#pragma once
#include <string>

namespace esphome
{
    namespace proxy_base
    {
        enum peer_state
        {
            PS_UNSET = 5,
            PS_PEER_ADDED = 10,
        };

        void describe_peer_state(std::string *output, peer_state state);
    } // namespace proxy_base
} // namespace esphome
