#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "../ripnetuk_ui/ripnetuk_switch_component.h"
#include "../ripnetuk_ui/ripnetuk_number_component.h"
#include "../ripnetuk_clock/ripnetuk_clock_component.h"
#include <Adafruit_NeoPixel.h>
#include "RGB.h"

namespace esphome
{
    namespace ripnetuk_lightshow_core
    {
        class RipnetUkLightshowCoreComponent : public Component
        {
        public:
            float get_setup_priority() const override;
            void set_clock(sensor::Sensor *clock) { _clock = clock; }
            void set_pixel_count(int pixel_count) { _pixel_count = pixel_count; }

        private:
            int _pixel_count;
            sensor::Sensor *_clock;
            RGB _pixels[200]; // TODO: MAKE THIS NICER but for now I only have 144 max...
        };
    } // namespace debug
} // namespace esphome
