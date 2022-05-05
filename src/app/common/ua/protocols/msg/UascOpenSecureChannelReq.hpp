#pragma once

#include "UascRequestHeader.hpp"
#include "UInt32.hpp"
#include "UascRequestType.hpp"
#include "UascSecurityMode.hpp"
#include "ByteString.hpp"

namespace app::ua
{

struct UascOpenSecureChannelReq
{
    UascRequestHeader       requestHdr;
    UInt32                  clientProtocolVer;
    UascRequestType         securityTokenRequestType;
    UascSecurityMode        securityMode;
    ByteString              clientNonce;
    UInt32                  requestLifetime;

};

} // namespace app::ua
