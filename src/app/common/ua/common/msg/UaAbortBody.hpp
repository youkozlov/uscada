#pragma once

#include "UInt32.hpp"
#include "String.hpp"

namespace app::ua
{

struct UaAbortBody
{
    UInt32                      error;
    String                      reason;
};

} // namespace app::ua
