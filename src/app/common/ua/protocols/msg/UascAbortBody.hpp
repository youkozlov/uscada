#pragma once

#include "UInt32.hpp"
#include "String.hpp"

namespace app::ua
{

struct UascAbortBody
{
    UInt32                      error;
    String                      reason;
};

} // namespace app::ua
