#pragma once

#include "UaMsgCont.hpp"
#include "UaResponseHeader.hpp"
#include "UInt32.hpp"
#include "UaChannelSecurityToken.hpp"
#include "ByteString.hpp"

namespace app::ua
{

struct UaOpenSecureChannelRsp
{
    UaResponseHeader            responseHdr;
    UInt32                      serverProtocolVer;
    UaChannelSecurityToken      securityToken;
    ByteString                  serverNonce;
};

using UaOpenSecureChannelRspCont = UaMsgCont<UaOpenSecureChannelRsp, DataTypeId::OpenSecureChannelResponse_Encoding_DefaultBinary>;

} // namespace app::ua
