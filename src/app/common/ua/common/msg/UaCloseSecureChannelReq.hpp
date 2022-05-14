#pragma once

#include "UaMsgCont.hpp"
#include "UaRequestHeader.hpp"
#include "UInt32.hpp"

namespace app::ua
{

struct UaCloseSecureChannelReq
{
    UaRequestHeader requestHdr;
};

using UaCloseSecureChannelReqCont = UaMsgCont<UaCloseSecureChannelReq, DataTypeId::CloseSecureChannelRequest_Encoding_DefaultBinary>;

} // namespace app::ua
