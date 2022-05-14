#include "UaActivateSession.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaSessionService.hpp"

namespace app::ua::service
{

UaActivateSession::UaActivateSession(UaSessionService& sessionService_)
    : sessionService(sessionService_)
{
}

UaActivateSession::~UaActivateSession()
{
}

void UaActivateSession::receive(UaEncodedMessageHdr const& hdr, OpcUaSduBuffer& rx)
{
    OpcUaBinaryCodec codec(rx);
    UaActivateSessionReq req;
    codec >> req;

    sessionService.receive(hdr, req);
}

} // namespace app::ua::service
