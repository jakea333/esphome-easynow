#pragma once

#include "esphome/core/component.h"
#include <vector>
#include "RGB.h"

namespace esphome
{
  namespace ripnetuk_lightshow_core
  {
    class Frame
    {
    public:
      Frame(int pixel_count);
      ~Frame();
      int time;
      std::vector<RGB*> *pixels;
      void set_all(RGB* rgb);
      // void mix_all(RGB* rgb);
    private:
    };

  } // namespace ripnetuk_lightshow_core
} // namespace esphome
