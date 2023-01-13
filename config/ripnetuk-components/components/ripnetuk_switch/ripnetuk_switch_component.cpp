#include "ripnetuk_switch_component.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace ripnetuk_switch
  {

    static const char *TAG = "ripnetuk_switch";

    // RipnetUkSwitchComponent::RipnetUkSwitchComponent() : turn_on_trigger_(new Trigger<>()), turn_off_trigger_(new Trigger<>()) {}

    // void RipnetUkSwitchComponent::loop()
    // {
    //   if (!this->f_.has_value())
    //     return;
    //   auto s = (*this->f_)();
    //   if (!s.has_value())
    //     return;

    //   this->publish_state(*s);
    // }

    void RipnetUkSwitchComponent::write_state(bool state)
    {
      _deviceSideState = state;
      this->publish_state(state);
      // if (this->prev_trigger_ != nullptr)
      // {
      //   this->prev_trigger_->stop_action();
      // }

      // if (state)
      // {
      //   this->prev_trigger_ = this->turn_on_trigger_;
      //   this->turn_on_trigger_->trigger();
      // }
      // else
      // {
      //   this->prev_trigger_ = this->turn_off_trigger_;
      //   this->turn_off_trigger_->trigger();
      // }

      // if (this->optimistic_)
      //   this->publish_state(state);
    }
    // void RipnetUkSwitchComponent::set_optimistic(bool optimistic) { this->optimistic_ = optimistic; }
    bool RipnetUkSwitchComponent::assumed_state()
    {
      return this->_deviceSideState;
    }

    // void RipnetUkSwitchComponent::set_state_lambda(std::function<optional<bool>()> &&f) { this->f_ = f; }
    float RipnetUkSwitchComponent::get_setup_priority() const
    {
      return setup_priority::HARDWARE;
    }

    // Trigger<> *RipnetUkSwitchComponent::get_turn_on_trigger() const { return this->turn_on_trigger_; }
    // Trigger<> *RipnetUkSwitchComponent::get_turn_off_trigger() const { return this->turn_off_trigger_; }
    void RipnetUkSwitchComponent::setup()
    {
      // if (!this->restore_state_)
      //   return;

      // optional<bool> initial_state = this->get_initial_state_with_restore_mode();

      // if (initial_state.has_value())
      // {
      //   ESP_LOGD(TAG, "  Restored state %s", ONOFF(initial_state.value()));
      //   // if it has a value, restore_mode is not "DISABLED", therefore act on the switch:
      //   if (initial_state.value())
      //   {
      //     this->turn_on();
      //   }
      //   else
      //   {
      //     this->turn_off();
      //   }
      // }
      _deviceSideState = false;
    }
    
    // void RipnetUkSwitchComponent::dump_config()
    // {
    //   LOG_SWITCH("", "Template Switch", this);
    //   ESP_LOGCONFIG(TAG, "  Restore State: %s", YESNO(this->restore_state_));
    //   ESP_LOGCONFIG(TAG, "  Optimistic: %s", YESNO(this->optimistic_));
    // }
    // void RipnetUkSwitchComponent::set_restore_state(bool restore_state) { this->restore_state_ = restore_state; }
    // void RipnetUkSwitchComponent::set_assumed_state(bool assumed_state) { this->assumed_state_ = assumed_state; }

  } // namespace template_
} // namespace esphome
