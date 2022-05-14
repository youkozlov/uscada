#pragma once

#include "UaConnectionId.hpp"
#include "UaSecureChannelId.hpp"
#include "UaRequestId.hpp"

namespace app
{

struct UaEncodedMessageHdr
{
    UaConnectionId      connectionId;
    UaSecureChannelId   secureChannelId;
    UaRequestId         requestId;
};


} // namespace app
