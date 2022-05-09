#pragma once

#include "Int32.hpp"

namespace app::ua
{

enum class UaUserTokenTypeEnum
{
      anonymous = 0
    , username
    , certificate
    , issuedtoken
};

using UaUserTokenType = Int32;

} // namespace app::ua
