#include "peer_state.h"
#include "esphome/core/log.h"

namespace esphome
{
    namespace proxy_base
    {
        PeerState::PeerState()
        {
            last_state_change_millis_ = millis();
            set_state(PS_NEW);
        }

        peer_state PeerState::get_state()
        {
            return state_;
        }

        void PeerState::set_state(peer_state state)
        {
            std::string old_desc;
            describe_state(&old_desc);

            state_ = state;

            std::string new_desc;
            describe_state(&new_desc);

            ESP_LOGD(TAG->get_tag(), "State change from %s to %s after %f3s", old_desc.c_str(), new_desc.c_str(), (millis()-last_state_change_millis_) / 1000.0);

            last_state_change_millis_ = millis();
        }

        void PeerState::describe_state(std::string *output)
        {
            switch (get_state())
            {
            case PS_NEW:
                output->append("NEW");
                break;
            default:
                output->append("!! UNKONWN PEER STATE TYPE !!");
            }
        }
    } // namespace proxy_base
} // namespace esphome
