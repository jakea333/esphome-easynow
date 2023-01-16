#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include <vector>
#include "../ripnetuk_ui/ripnetuk_switch_component.h"
#include "../ripnetuk_ui/ripnetuk_number_component.h"
#include "../ripnetuk_clock/ripnetuk_clock_component.h"
#include "base_ripnetuk_lightshow_input_component.h"
#include "base_ripnetuk_lightshow_output_component.h"

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
            void set_clock(ripnetuk_clock::RipnetUkClockComponent *clock) { _clock = clock; }
            void set_pixel_count(int pixel_count) { _pixel_count = pixel_count; }
            int get_pixel_count() { return _pixel_count; }
            ripnetuk_clock::RipnetUkClockComponent *get_clock() { return _clock; }
            RGB _pixels[200]; // TODO: MAKE THIS NICER but for now I only have 144 max...
            void add_input(BaseRipnetUkLightshowInputComponent *input) { _inputs->push_back(input); }
            void add_output(BaseRipnetUkLightshowOutputComponent *output) { _outputs->push_back(output); }
            void loop() override;
        private:
            int _pixel_count;
            std::vector<BaseRipnetUkLightshowOutputComponent *> *_outputs = new std::vector<BaseRipnetUkLightshowOutputComponent *>();
            std::vector<BaseRipnetUkLightshowInputComponent *> *_inputs = new std::vector<BaseRipnetUkLightshowInputComponent *>();
            ripnetuk_clock::RipnetUkClockComponent *_clock;
        };
    } // namespace debug
} // namespace esphome
