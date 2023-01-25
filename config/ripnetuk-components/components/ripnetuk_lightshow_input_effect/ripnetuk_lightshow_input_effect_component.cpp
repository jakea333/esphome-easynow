#include "ripnetuk_lightshow_input_effect_component.h"
#include "esphome/core/log.h"
#include "esphome.h"
#include "../ripnetuk_lightshow_core/RGB.h"

#define RANGESIZE 1500

namespace esphome
{
    namespace ripnetuk_lightshow_input_effect
    {
        static const char *TAG = "ripnetuk_lightshow_input_effect";

        float RipnetUkLightshowInputEffectComponent::get_setup_priority() const
        {
            return setup_priority::HARDWARE;
        }
        
        void RipnetUkLightshowInputEffectComponent::setup()
        {
            // _ha_use_fake_state->set(false);
            // _ha_fake_state->set(500);
        }

        void RipnetUkLightshowInputEffectComponent::input_frame(ripnetuk_lightshow_core::Frame *frame)
        {
            // float realPower = _sensor->state;
            // float fakePower = _ha_fake_state->state;
            // bool useFakePower = _ha_use_fake_state->state;

            // if (isnan(realPower))
            // {
            //     drawHoldingPattern(frame);
            // }
            // else
            // {
            //     float measuredPower = useFakePower ? fakePower : realPower;

            //     float deltaNeeded = measuredPower - _currentDisplayState;
            //     // Limit change speed to get an animation
            //     float maxDelta = RANGESIZE / frame->pixels->size() * 2; // 4 led per cycle

            //     float deltaToApply = deltaNeeded;
            //     if (deltaToApply > maxDelta)
            //     {
            //         deltaToApply = maxDelta;
            //     }
            //     if (deltaToApply < (0 - maxDelta))
            //     {
            //         deltaToApply = 0 - maxDelta;
            //     }
            //     _currentDisplayState += deltaToApply;
            //     drawPower(frame, _currentDisplayState);
            // }
        }
    }
}
