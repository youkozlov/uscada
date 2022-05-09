#pragma once

#include "Int32.hpp"

namespace app::ua
{

enum class UaApplicationTypeEnum
{
      server = 0
    , client
    , clientandserver
    , discoveryserver
};

using UaApplicationType = Int32;

} // namespace app::ua
