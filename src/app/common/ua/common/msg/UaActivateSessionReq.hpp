#pragma once

#include "UaMsgCont.hpp"
#include "UaRequestHeader.hpp"
#include "UaSignatureData.hpp"
#include "LocaleId.hpp"
#include "UaUserIdentityToken.hpp"

namespace app::ua
{

struct UaActivateSessionReq
{
    UaRequestHeader                     requestHdr;
    UaSignatureData                     clientSignature;
    DynamicArray<Byte>                  clientSoftwareCertificates;
    DynamicArray<LocaleId>              localeIds;
    UaUserIdentityToken                 userIdentityToken;
    UaSignatureData                     userTokenSignature;
};

using UaActivateSessionReqCont = UaMsgCont<UaActivateSessionReq, DataTypeId::ActivateSessionRequest_Encoding_DefaultBinary>;

} // namespace app::ua
