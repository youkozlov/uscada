#pragma once

#include "UaMsgCont.hpp"
#include "UaResponseHeader.hpp"

namespace app::ua
{

struct UaCloseSecureChannelRsp
{
    UaResponseHeader responseHdr;
};

using UaCloseSecureChannelRspCont = UaMsgCont<UaCloseSecureChannelRsp, DataTypeId::CloseSecureChannelResponse_Encoding_DefaultBinary>;

} // namespace app::ua
