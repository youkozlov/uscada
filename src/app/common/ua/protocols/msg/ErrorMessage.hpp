#pragma once

#include "UInt32.hpp"
#include "String.hpp"

namespace ua
{

struct ErrorMessage
{
    UInt32 error;
    String reason;
};

} // namespace ua
