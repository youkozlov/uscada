#pragma once

#include "ComponentId.hpp"

namespace app
{

enum CompIds : reactor::ComponentId
{
      connector = 0
    , detector
    , controller
    , modbus
};

} // namespace app
