#include "UaCreateSession.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaSessionService.hpp"

namespace app::ua::service
{

UaCreateSession::UaCreateSession(UaSessionService& sessionService_)
    : sessionService(sessionService_)
{
}

UaCreateSession::~UaCreateSession()
{
}

void UaCreateSession::receive(UaEncodedMessageHdr const& hdr, OpcUaSduBuffer& rx)
{
    OpcUaBinaryCodec codec(rx);
    UaCreateSessionReq req;
    codec >> req;

    sessionService.receive(hdr, req);
}

} // namespace app::ua::service
