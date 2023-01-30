#include "proxy_payload.h"

namespace esphome
{
    namespace proxy_base
    {

        int ProxyPayload::get_magic_number()
        {
            return 42;
        }
    } // namespace proxy_base
} // namespace esphome
