#pragma once
#include <string>
#include "log_tag.h"

namespace esphome
{
    namespace proxy_base
    {
        enum peer_state
        {
            PS_NEW = 10,
        };

        class PeerState
        {
        private:
            peer_state state_;
            int last_state_change_millis_;

        public:
            PeerState();
            peer_state get_state();
            void set_state(peer_state state);
            void describe_state(std::string *output);

        protected:
            LogTag *TAG = new LogTag("PeerState");
        };
    } // namespace proxy_base
} // namespace esphome
