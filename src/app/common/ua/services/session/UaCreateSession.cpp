#include "UaCreateSession.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaSessionController.hpp"
#include "UaCreateSessionReq.hpp"
#include "UaCreateSessionRsp.hpp"

namespace app::ua
{

UaCreateSession::UaCreateSession(UaSessionController& sessionController_)
    : sessionController(sessionController_)
{
}

UaCreateSession::~UaCreateSession()
{
}

void UaCreateSession::process(OpcUaSecureChannel& channel)
{
    OpcUaBinaryCodec codec(channel.getRxBuffer());
    UaCreateSessionReq req;
    codec >> req;

    sessionController.receive(req, [&channel](auto const& rsp) { channel.send(rsp); });
}

} // namespace app::ua
