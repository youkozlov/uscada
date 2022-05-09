#pragma once

#include "UaMsgCont.hpp"
#include "UaResponseHeader.hpp"
#include "ByteString.hpp"
#include "StatusCode.hpp"
#include "DiagnosticInfo.hpp"

namespace app::ua
{

struct UaActivateSessionRsp
{
    UaResponseHeader                responseHdr;
    ByteString                      serverNonce;
    DynamicArray<StatusCode>        results;
    DynamicArray<DiagnosticInfo>    diagnosticInfos;
};

using UaActivateSessionRspCont = UaMsgCont<UaActivateSessionRsp, DataTypeId::ActivateSessionResponse_Encoding_DefaultBinary>;

} // namespace app::ua
