#pragma once

#include "UaMsgCont.hpp"
#include "UaRequestHeader.hpp"
#include "Duration.hpp"
#include "TimestampsToReturn.hpp"
#include "ReadValueId.hpp"

namespace app::ua
{

struct UaReadReq
{
    UaRequestHeader             requestHdr;
    Duration                    maxAge;
    TimestampsToReturn          timestampsToReturn;
    DynamicArray<ReadValueId>   nodesToRead;
};

using UaReadReqCont = UaMsgCont<UaReadReq, DataTypeId::ReadRequest_Encoding_DefaultBinary>;

} // namespace app::ua
