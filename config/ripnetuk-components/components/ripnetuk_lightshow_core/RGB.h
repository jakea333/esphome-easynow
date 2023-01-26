#pragma once

#define ON_BRIGHTNESS 0.8

namespace esphome
{
    namespace ripnetuk_lightshow_core
    {
        class RGB
        {
        public:
            float r;
            float g;
            float b;
            void set(RGB *rgb);
            void set_from_hsv(float h, float s, float v);
            void scale(float multiplier);
            void dump_to_log();
            bool is_black();
        };

        const RGB OFF_PIXEL = {0, 0, 0};

        const RGB rangeRGBs[] = {
            {0, 0, ON_BRIGHTNESS},
            {0, ON_BRIGHTNESS, 0},
            {ON_BRIGHTNESS, ON_BRIGHTNESS, 0},
            {ON_BRIGHTNESS, 0, 0},
            {ON_BRIGHTNESS, 0, ON_BRIGHTNESS},
            {0, ON_BRIGHTNESS, ON_BRIGHTNESS},
            {ON_BRIGHTNESS, ON_BRIGHTNESS, ON_BRIGHTNESS}};
    }
}