#include "ripnetuk_clock_component.h"
#include "esphome/core/log.h"

namespace esphome
{
  namespace ripnetuk_clock
  {

    static const char *TAG = "ripnetuk_clock";

    void RipnetUkClockComponent::setup()
    {
    }
    
    void RipnetUkClockComponent::update()
    {
    }

    float RipnetUkClockComponent::get_setup_priority() const
    {
      return setup_priority::LATE;
    }

  } // namespace debug
} // namespace esphome
