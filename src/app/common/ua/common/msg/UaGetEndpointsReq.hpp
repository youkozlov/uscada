#pragma once

#include "UaMsgCont.hpp"
#include "UaRequestHeader.hpp"
#include "String.hpp"

namespace app::ua
{

struct UaGetEndpointsReq
{
    UaRequestHeader         requestHdr;
    String                  endpointUrl;
    DynamicArray<String>    localeIds;
    DynamicArray<String>    profileUris;
};

using UaGetEndpointsReqCont = UaMsgCont<UaGetEndpointsReq, DataTypeId::GetEndpointsRequest_Encoding_DefaultBinary>;

} // namespace app::ua
