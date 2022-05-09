#pragma once

#include "UaMsgCont.hpp"
#include "UaResponseHeader.hpp"
#include "NodeId.hpp"
#include "UaSessionAuthentificationToken.hpp"
#include "String.hpp"
#include "ByteString.hpp"
#include "Duration.hpp"
#include "UaSignatureData.hpp"

namespace app::ua
{

struct UaCreateSessionRsp
{
    UaResponseHeader                        responseHdr;
    NodeId                                  sessionId;
    UaSessionAuthentificationToken          authenticationToken;
    Duration                                revisedSessionTimeout;
    ByteString                              serverNonce;
    ByteString                              serverCertificate;
    DynamicArray<UaEndpointDescription>     serverEndpoints;
    DynamicArray<Byte>                      signedSoftwareCertificate;
    UaSignatureData                         serverSignature;
    UInt32                                  maxRequestMessageSize;
};

using UaCreateSessionRspCont = UaMsgCont<UaCreateSessionRsp, DataTypeId::CreateSessionResponse_Encoding_DefaultBinary>;

} // namespace app::ua
