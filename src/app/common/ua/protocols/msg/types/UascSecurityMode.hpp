#pragma once

#include "Int32.hpp"

namespace app::ua
{

enum class UascSecurityModeEnum
{
      invalid = 0
    , none
    , sign
    , signandencrypt
};

using UascSecurityMode = Int32;

} // namespace app::ua
