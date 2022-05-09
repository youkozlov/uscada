#pragma once

#include "UaMsgCont.hpp"
#include "UaRequestHeader.hpp"
#include "UInt32.hpp"
#include "UaRequestType.hpp"
#include "UaSecurityMode.hpp"
#include "ByteString.hpp"

namespace app::ua
{

struct UaOpenSecureChannelReq
{
    UaRequestHeader         requestHdr;
    UInt32                  clientProtocolVer;
    UaRequestType           securityTokenRequestType;
    UaSecurityMode          securityMode;
    ByteString              clientNonce;
    UInt32                  requestLifetime;
};

using UaOpenSecureChannelReqCont = UaMsgCont<UaOpenSecureChannelReq, DataTypeId::OpenSecureChannelRequest_Encoding_DefaultBinary>;

} // namespace app::ua
