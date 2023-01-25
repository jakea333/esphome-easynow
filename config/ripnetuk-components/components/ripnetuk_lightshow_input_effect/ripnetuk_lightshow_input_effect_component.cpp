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
            _ha_effect->set(1);
        }

        void RipnetUkLightshowInputEffectComponent::input_frame(ripnetuk_lightshow_core::Frame *frame)
        {
            int effect = _ha_effect->state;

            for (int i = 0; i < frame->pixels->size(); i++)
            {
                int index = (frame->time / 500) + i;
                ESP_LOGD(TAG, "index %d", index);
                if (effect == 1)
                {
                    ripnetuk_lightshow_core::RGB col = {0, 0, 0};

                    col.r = (index % 100) / 100.0;
                    col.g = (index % 200) / 200.0;
                    col.b = (index % 400) / 400.0;

                    col.dump_to_log();

                    frame->pixels->at(i)->mix(&col);
                }
            }
        }
    }
}
