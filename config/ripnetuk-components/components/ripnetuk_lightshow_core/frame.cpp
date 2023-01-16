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
      Pixels = new std::vector<RGB *>();

      for (int i = 0; i < pixel_count; i++)
      {
        RGB *rgb = new RGB();
        rgb->r = i * 10;
        rgb->g = i * 2;
        rgb->g = i;
        Pixels->push_back(rgb);
      }
    }

    Frame::~Frame()
    {
      for (int i = 0; i < Pixels->size(); i++)
      {
        delete (Pixels->at(i));
      }
      Pixels->clear();
      delete (Pixels);
    }

    void Frame::set_all(RGB *rgb)
    {
      for (int i = 0; i < Pixels->size(); i++)
      {
        Pixels->at(i)->r = rgb->r;
        Pixels->at(i)->g = rgb->g;
        Pixels->at(i)->b = rgb->b;
      }
    }
  }
}
