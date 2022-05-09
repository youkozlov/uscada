#pragma once

#include "UaMsgCont.hpp"
#include "UaRequestHeader.hpp"
#include "UaApplicationDescription.hpp"
#include "UaApplicationInstanceCertificate.hpp"
#include "String.hpp"
#include "Duration.hpp"

namespace app::ua
{

struct UaCreateSessionReq
{
    UaRequestHeader                     requestHdr;
    UaApplicationDescription            clientDescription;
    String                              serverUri;
    String                              endpointUrl;
    String                              sessionName;
    ByteString                          clientNonce;
    UaApplicationInstanceCertificate    clientCertificate;
    Duration                            requestedSessionTimeout;
    UInt32                              maxResponseMessageSize;
};

using UaCreateSessionReqCont = UaMsgCont<UaCreateSessionReq, DataTypeId::CreateSessionRequest_Encoding_DefaultBinary>;

} // namespace app::ua
