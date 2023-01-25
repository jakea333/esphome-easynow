#include "frame.h"
#include "esphome/core/log.h"
#include "esphome.h"

namespace esphome
{
  namespace ripnetuk_lightshow_core
  {
    static const char *TAG = "frame";

    Frame::Frame(int pixel_count)
    {
      pixels = new std::vector<RGB *>();

      for (int i = 0; i < pixel_count; i++)
      {
        RGB *rgb = new RGB();
        rgb->r = i * 10;
        rgb->g = i * 2;
        rgb->g = i;
        pixels->push_back(rgb);
      }
    }

    Frame::~Frame()
    {
      for (int i = 0; i < pixels->size(); i++)
      {
        delete (pixels->at(i));
      }
      pixels->clear();
      delete (pixels);
    }

    void Frame::set_all(RGB *rgb)
    {
      for (int i = 0; i < pixels->size(); i++)
      {
        pixels->at(i)->set(rgb);
      }
    }
    
    void Frame::mix_all(RGB *rgb)
    {
      for (int i = 0; i < pixels->size(); i++)
      {
        pixels->at(i)->mix(rgb);
      }
    }

  }
}
