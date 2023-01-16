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
      std::vector<RGB*> *Pixels;

    private:
    };

  } // namespace ripnetuk_lightshow_core
} // namespace esphome
