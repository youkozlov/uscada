#pragma once

#include "UaMsgCont.hpp"
#include "UaResponseHeader.hpp"
#include "DataValue.hpp"

namespace app::ua
{

struct UaReadRsp
{
    UaResponseHeader                responseHdr;
    DynamicArray<DataValue>         results;
    DynamicArray<DiagnosticInfo>    diagnosticInfos;
};

using UaReadRspCont = UaMsgCont<UaReadRsp, DataTypeId::ReadResponse_Encoding_DefaultBinary>;

} // namespace app::ua
