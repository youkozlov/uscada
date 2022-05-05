#pragma once

#include "UascResponseHeader.hpp"
#include "UInt32.hpp"
#include "UascChannelSecurityToken.hpp"
#include "ByteString.hpp"

namespace app::ua
{

struct UascOpenSecureChannelRsp
{
    UascResponseHeader          responseHdr;
    UInt32                      serverProtocolVer;
    UascChannelSecurityToken    securityToken;
    ByteString                  serverNonce;
};

} // namespace app::ua
