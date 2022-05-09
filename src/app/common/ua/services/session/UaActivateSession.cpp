#include "UaActivateSession.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaSessionController.hpp"
#include "UaActivateSessionReq.hpp"
#include "UaActivateSessionRsp.hpp"

namespace app::ua
{

UaActivateSession::UaActivateSession(UaSessionController& sessionController_)
    : sessionController(sessionController_)
{
}

UaActivateSession::~UaActivateSession()
{
}

void UaActivateSession::process(OpcUaSecureChannel& channel)
{
    OpcUaBinaryCodec codec(channel.getRxBuffer());
    UaActivateSessionReq req;
    codec >> req;

    sessionController.receive(req, [&channel](auto const& rsp) { channel.send(rsp); });
}

} // namespace app::ua
