#include "RGB.h"

namespace esphome
{
    namespace ripnetuk_lightshow_core
    {
        void RGB::set(RGB *rgb)
        {
            r = rgb->r;
            g = rgb->g;
            b = rgb->b;
            brightness = rgb->brightness;
        }
    }
}