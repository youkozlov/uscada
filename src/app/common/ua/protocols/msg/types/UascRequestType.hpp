#pragma once

#include "Int32.hpp"

namespace app::ua
{

enum class UascRequestTypeEnum
{
      issue = 0
    , renew
};

using UascRequestType = Int32;

} // namespace app::ua
