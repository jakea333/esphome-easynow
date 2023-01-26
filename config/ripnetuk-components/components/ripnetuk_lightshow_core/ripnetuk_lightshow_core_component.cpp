#include "ripnetuk_lightshow_core_component.h"
#include "esphome/core/log.h"
#include "esphome.h"
#include "frame.h"

namespace esphome
{
    namespace ripnetuk_lightshow_core
    {
        static const char *TAG = "ripnetuk_lightshow_core";

        float RipnetUkLightshowCoreComponent::get_setup_priority() const
        {
            return setup_priority::HARDWARE;
        }

        float RipnetUkLightshowCoreComponent::merge_channel(float target, float to_merge)
        {
            if (to_merge > target)
                return to_merge;
            return target;
        }

        void RipnetUkLightshowCoreComponent::merge_frame(Frame *target, Frame *to_merge)
        {
            for (int i = 0; i < target->pixels->size(); i++)
            {
                target->pixels->at(i)->r = merge_channel(target->pixels->at(i)->r, to_merge->pixels->at(i)->r);
                target->pixels->at(i)->g = merge_channel(target->pixels->at(i)->g, to_merge->pixels->at(i)->g);
                target->pixels->at(i)->b = merge_channel(target->pixels->at(i)->b, to_merge->pixels->at(i)->b);
            }
        }

        void RipnetUkLightshowCoreComponent::loop()
        {
            Frame *frame = new Frame(_pixel_count);
            frame->time = _clock->time();
            // float ani = (_clock->time() % 1000);
            // ani = ani / 1000.0;
            // RGB rgb = RGB{1, 0, ani};
            // frame->set_all(&rgb);

            RGB blank = RGB{0, 0, 0};

            frame->set_all(&blank);

            for (int i = 0; i < _inputs->size(); i++)
            {
                Frame *input_frame = new Frame(_pixel_count);
                input_frame->time = frame->time;
                _inputs->at(i)->input_frame(input_frame, frame);
                merge_frame(frame, input_frame);
                delete (input_frame);
            }

            for (int i = 0; i < _outputs->size(); i++)
            {
                _outputs->at(i)->output_frame(frame);
            }
            delete (frame);
        }
    }
}
