#pragma once

#include "String.hpp"
#include "ByteString.hpp"

namespace app::ua
{

struct UaSignatureData
{
    String                  algorithm;
    ByteString              signature;
};

} // namespace app::ua
