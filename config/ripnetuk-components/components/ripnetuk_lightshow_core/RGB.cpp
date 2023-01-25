#include "RGB.h"
#include "esphome/core/log.h"

namespace esphome
{
    namespace ripnetuk_lightshow_core
    {
        static const char *TAG = "RGB";

        void RGB::set(RGB *rgb)
        {
            r = rgb->r;
            g = rgb->g;
            b = rgb->b;
        }

        void RGB::mix(RGB *rgb)
        {
            if (rgb->r > r)
                r = rgb->r;
            if (rgb->g > g)
                g = rgb->g;
            if (rgb->b > b)
                b = rgb->b;
        }

        void RGB::scale(float multiplier)
        {
            r = r * multiplier;
            g = g * multiplier;
            b = b * multiplier;
        }

        void RGB::dump_to_log()
        {
            ESP_LOGD(TAG, "%f %f %f", r, g, b);
        }
    }
}