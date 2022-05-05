#pragma once

#include "UInt32.hpp"
#include "MsgUtils.hpp"

namespace app::ua
{

struct UascSequenceHeader
{
    UInt32                  sequenceNumber;
    UInt32                  requestId;
};

} // namespace app::ua
