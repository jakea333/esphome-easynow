#pragma once
#include "esphome/components/ota/ota_backend.h"

namespace esphome
{
    namespace proxy_base
    {

        class OtaHolder
        {
        private:
            ota::OTAComponent *ota_;

        public:
            void set_ota(ota::OTAComponent *ota) { ota_ = ota; }
            ota::OTAComponent *get_ota() { return ota_; }
        };
    }
}
