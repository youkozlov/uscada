#include "UaCloseSession.hpp"
#include "OpcUaBinaryCodec.hpp"
#include "UaSessionController.hpp"
#include "UaCloseSessionReq.hpp"
#include "UaCloseSessionRsp.hpp"

namespace app::ua
{

UaCloseSession::UaCloseSession(UaSessionController& sessionController_)
    : sessionController(sessionController_)
{
}

UaCloseSession::~UaCloseSession()
{
}

void UaCloseSession::process(OpcUaSecureChannel& channel)
{
    OpcUaBinaryCodec codec(channel.getRxBuffer());
    UaCloseSessionReq req;
    codec >> req;

    sessionController.receive(req, [&channel](auto const& rsp) { channel.send(rsp); });
}

} // namespace app::ua
