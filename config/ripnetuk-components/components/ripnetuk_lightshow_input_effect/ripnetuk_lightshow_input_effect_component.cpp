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
            _ha_effect->set(3);
            _ha_s->set(0.7);
            _ha_v->set(0.2);
        }

        void RipnetUkLightshowInputEffectComponent::input_frame(ripnetuk_lightshow_core::Frame *frame)
        {
            int effect = _ha_effect->state;
            float time_for_entire_length = 3000;
            float time_per_pixel = time_for_entire_length / frame->pixels->size();

            int start_index = frame->time / time_per_pixel;

            start_index += 12883; // start somewhere interesting

            for (int i = 0; i < frame->pixels->size(); i++)
            {

                ripnetuk_lightshow_core::RGB col = {0, 0, 0};

                if (effect == 1)
                {
                    int index = i + start_index;
                    col.r = (index % 100) / 200.0;
                    col.g = (index % 200) / 400.0;
                    col.b = (index % 400) / 800.0;
                }

                if (effect == 2)
                {
                    int index = i + start_index;
                    float h = index % 360;
                    float s = _ha_s->state;
                    float v = _ha_v->state;
                    col.set_from_hsv(h, s, v);
                }

                if (effect == 3)
                {
                    int index = start_index - i + 720;
                    float h = index % 360;
                    float s = _ha_s->state;
                    float v = _ha_v->state;
                    col.set_from_hsv(h, s, v);
                }

                frame->pixels->at(i)->set(&col);
            }
        }
    }
}
