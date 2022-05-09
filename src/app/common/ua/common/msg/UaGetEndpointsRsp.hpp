#pragma once

#include "UaMsgCont.hpp"
#include "UaResponseHeader.hpp"
#include "UaEndpointDescription.hpp"

namespace app::ua
{

struct UaGetEndpointsRsp
{
    UaResponseHeader                        responseHdr;
    DynamicArray<UaEndpointDescription>     endpointDescription;
};

using UaGetEndpointsRspCont = UaMsgCont<UaGetEndpointsRsp, DataTypeId::GetEndpointsResponse_Encoding_DefaultBinary>;

} // namespace app::ua
