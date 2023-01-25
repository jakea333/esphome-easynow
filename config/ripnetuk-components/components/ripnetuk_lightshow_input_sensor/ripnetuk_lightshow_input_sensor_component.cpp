#include "ripnetuk_lightshow_input_sensor_component.h"
#include "esphome/core/log.h"
#include "esphome.h"
#include "../ripnetuk_lightshow_core/RGB.h"

#define RANGESIZE 1500

namespace esphome
{
    namespace ripnetuk_lightshow_input_sensor
    {
        static const char *TAG = "ripnetuk_lightshow_input_sensor";

        float RipnetUkLightshowInputSensorComponent::get_setup_priority() const
        {
            return setup_priority::HARDWARE;
        }
        
        void RipnetUkLightshowInputSensorComponent::setup()
        {
            _ha_use_fake_state->set(false);
            _ha_fake_state->set(500);
        }

        void RipnetUkLightshowInputSensorComponent::input_frame(ripnetuk_lightshow_core::Frame *frame)
        {
            float realPower = _sensor->state;
            float fakePower = _ha_fake_state->state;
            bool useFakePower = _ha_use_fake_state->state;

            if (isnan(realPower))
            {
                drawHoldingPattern(frame);
            }
            else
            {
                float measuredPower = useFakePower ? fakePower : realPower;

                float deltaNeeded = measuredPower - _currentDisplayState;
                // Limit change speed to get an animation
                float maxDelta = RANGESIZE / frame->pixels->size() * 2; // 4 led per cycle

                float deltaToApply = deltaNeeded;
                if (deltaToApply > maxDelta)
                {
                    deltaToApply = maxDelta;
                }
                if (deltaToApply < (0 - maxDelta))
                {
                    deltaToApply = 0 - maxDelta;
                }
                _currentDisplayState += deltaToApply;
                drawPower(frame, _currentDisplayState);
            }
        }

        void RipnetUkLightshowInputSensorComponent::drawHoldingPattern(ripnetuk_lightshow_core::Frame *frame)
        {
            int activeLed = (frame->time / 200) % frame->pixels->size();

            for (int i = 0; i < frame->pixels->size(); i++)
            {
                ripnetuk_lightshow_core::RGB pxl = ripnetuk_lightshow_core::OFF_PIXEL;

                pxl.r = 0;
                pxl.g = 0;
                pxl.b = 0;

                if (WiFi.status() != WL_CONNECTED)
                {
                    pxl.b = (i == activeLed) ? 1 : 0;
                }
                else
                {
                    pxl.g = (i == activeLed) ? 1 : 0;
                }
                frame->pixels->at(i)->set(&pxl);
            }
        }

        void RipnetUkLightshowInputSensorComponent::drawOutOfRange(ripnetuk_lightshow_core::Frame *frame, ripnetuk_lightshow_core::RGB *rgb)
        {
            bool isOn = ((frame->time / 500) % 2) != 0;

            ripnetuk_lightshow_core::RGB color = isOn ? *rgb : ripnetuk_lightshow_core::OFF_PIXEL;
            frame->set_all(&color);
        }

        void RipnetUkLightshowInputSensorComponent::drawPower(ripnetuk_lightshow_core::Frame *frame, float power)
        {
            int rangeRGBCount = sizeof(ripnetuk_lightshow_core::rangeRGBs) / sizeof(ripnetuk_lightshow_core::rangeRGBs[0]);

            // Figure out which range we are in...
            int rangeIndex = power / RANGESIZE;
            // ESP_LOGD(TAG, "Draw Power %f range index %d", power, rangeIndex);
            //  Check we are in range...
            if (power < 0)
            {
                ripnetuk_lightshow_core::RGB rgb = {1, 0, 0};
                drawOutOfRange(frame, &rgb);
                return;
            }
            if (rangeIndex >= rangeRGBCount)
            {
                ripnetuk_lightshow_core::RGB rgb = {1, 10, 1};
                drawOutOfRange(frame, &rgb);
                return;
            }

            float rangeStart = rangeIndex * RANGESIZE;

            float positionInRange = power - rangeStart;

            // We reseerve 1 LED so we can anlways tell what range is

            float lengthPerLED = RANGESIZE / (frame->pixels->size() - 1);

            int ledsToLight = positionInRange / lengthPerLED;
            float remainder = positionInRange - (ledsToLight * lengthPerLED);

            float remainderBrightness = remainder / lengthPerLED;

            // ESP_LOGD(TAG, "Measured Power %f - PositionInRange %f - rangeLength %f - lengthPerLED %f - remainder %f -- LEDS to Light %d remainderBrightness %f", power, positionInRange, rangeLength, lengthPerLED, remainder, ledsToLight, remainderBrightness);

            ripnetuk_lightshow_core::RGB rangeRGB = ripnetuk_lightshow_core::rangeRGBs[rangeIndex];

            for (int i = 0; i < frame->pixels->size(); i++)
            {
                ripnetuk_lightshow_core::RGB pxl = ripnetuk_lightshow_core::OFF_PIXEL;
                // Always light first one
                if (i == 0)
                {
                    pxl = rangeRGB;
                }
                // Light up completely filled lights
                if (i <= ledsToLight)
                {
                    pxl = rangeRGB;
                }
                // Light up next LED as remainer
                if (i == ledsToLight + 1)
                {
                    pxl = rangeRGB;
                    pxl.scale(remainderBrightness);
                }
                frame->pixels->at(i)->set(&pxl);
            }
        }
    }
}
