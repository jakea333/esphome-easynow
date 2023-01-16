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
            return setup_priority::LATE;
        }

        void RipnetUkLightshowCoreComponent::loop()
        {
            Frame *frame = new Frame(_pixel_count);
            RGB rgb = RGB{1, 0, 0, 1};
            frame->set_all(&rgb);

            for (int i = 0; i < _outputs->size(); i++)
            {
                _outputs->at(i)->output_frame(frame);
            }
            delete (frame);
        }
    }
}
