#pragma once

#include "UaMsgCont.hpp"
#include "UaResponseHeader.hpp"

namespace app::ua
{

struct UaCloseSessionRsp
{
    UaResponseHeader responseHdr;
};

using UaCloseSessionRspCont = UaMsgCont<UaCloseSessionRsp, DataTypeId::CloseSessionResponse_Encoding_DefaultBinary>;

} // namespace app::ua
