#pragma once

#include "ComponentId.hpp"

namespace app
{

enum CompIds : reactor::ComponentId
{
      compConnector = 0
    , compDetector
    , compController
    , compModbus
    , compUaTransport
    , compUaSecChannel
    , compUaService
};

} // namespace app
