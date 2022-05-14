#include "UaCloseSession.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaSessionService.hpp"

namespace app::ua::service
{

UaCloseSession::UaCloseSession(UaSessionService& sessionService_)
    : sessionService(sessionService_)
{
}

UaCloseSession::~UaCloseSession()
{
}

void UaCloseSession::receive(UaEncodedMessageHdr const& hdr, OpcUaSduBuffer& rx)
{
    OpcUaBinaryCodec codec(rx);
    UaCloseSessionReq req;
    codec >> req;

    sessionService.receive(hdr, req);
}

} // namespace app::ua::service