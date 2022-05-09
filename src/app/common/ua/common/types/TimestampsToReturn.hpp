#pragma once

#include "Int32.hpp"

namespace app::ua
{

enum class TimestampsToReturnEnum
{
      source = 0
    , server
    , both
    , neither
    , invalid
};

using TimestampsToReturn = Int32;

inline std::int32_t toInt32(TimestampsToReturnEnum val)
{
    return static_cast<std::int32_t>(val);
}

} // namespace app::ua
