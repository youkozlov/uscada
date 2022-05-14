#pragma once

#include "UaConnectionId.hpp"
#include "UaSecureChannelId.hpp"
#include "UaRequestId.hpp"
#include "UaSessionId.hpp"

namespace app
{

struct UaEncodedMessageHdr
{
    UaConnectionId      connectionId;
    UaSecureChannelId   secureChannelId;
    UaRequestId         requestId;
    UaSessionId         sessionId;
};


} // namespace app
