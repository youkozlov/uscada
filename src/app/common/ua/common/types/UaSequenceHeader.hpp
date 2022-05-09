#pragma once

#include "UInt32.hpp"
#include "MsgUtils.hpp"

namespace app::ua
{

struct UaSequenceHeader
{
    UInt32                  sequenceNumber;
    UInt32                  requestId;
};

} // namespace app::ua
