#pragma once

#include "Int32.hpp"

namespace app::ua
{

enum class UaSecurityModeEnum
{
      invalid = 0
    , none
    , sign
    , signandencrypt
};

using UaSecurityMode = Int32;

inline std::int32_t toInt32(UaSecurityModeEnum val)
{
    return static_cast<std::int32_t>(val);
}

} // namespace app::ua
