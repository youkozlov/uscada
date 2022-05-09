#pragma once

#include "UaMsgCont.hpp"
#include "UaRequestHeader.hpp"
#include "Boolean.hpp"

namespace app::ua
{

struct UaCloseSessionReq
{
    UaRequestHeader requestHdr;
    Boolean         deleteSubscriptions;
};

using UaCloseSessionReqCont = UaMsgCont<UaCloseSessionReq, DataTypeId::CloseSessionRequest_Encoding_DefaultBinary>;

} // namespace app::ua
