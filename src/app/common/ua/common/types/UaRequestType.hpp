#pragma once

#include "Int32.hpp"

namespace app::ua
{

enum class UaRequestTypeEnum
{
      issue = 0
    , renew
};

using UaRequestType = Int32;

} // namespace app::ua
