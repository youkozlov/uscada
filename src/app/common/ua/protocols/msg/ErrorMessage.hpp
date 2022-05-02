#pragma once

#include "UInt32.hpp"
#include "String.hpp"

namespace app::ua
{

struct ErrorMessage
{
    UInt32 error;
    String reason;
};

} // namespace app::ua
