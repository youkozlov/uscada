#pragma once

#include "UInt32.hpp"

namespace ua
{

struct AcknowledgeMessage
{
    UInt32 protocolVersion;
    UInt32 receiveBufferSize;
    UInt32 sendBufferSize;
    UInt32 maxMessageSize;
    UInt32 maxChunkCount;
};

} // namespace ua
