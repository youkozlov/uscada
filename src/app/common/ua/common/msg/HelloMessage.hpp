#pragma once

#include "UInt32.hpp"
#include "String.hpp"

namespace app::ua
{

struct HelloMessage
{
    UInt32 protocolVersion;
    UInt32 receiveBufferSize;
    UInt32 sendBufferSize;
    UInt32 maxMessageSize;
    UInt32 maxChunkCount;
    String endpointUrl;
};

} // namespace app::ua
