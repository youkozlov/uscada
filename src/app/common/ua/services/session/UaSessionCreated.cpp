#include "UaSessionCreated.hpp"
#include "UaSessionActivated.hpp"
#include "UaSessionInit.hpp"
#include "UaSession.hpp"

namespace app::ua
{

void UaSessionCreated::onActivate(UaSession& fsm, UaActivateSessionReq const& req, UaServiceHandler handler)
{
    fsm.activate(req, handler);
    fsm.transit<UaSessionActivated>();
}

void UaSessionCreated::onClose(UaSession& fsm, UaCloseSessionReq const& req, UaServiceHandler handler)
{
    fsm.close(req, handler);
    fsm.transit<UaSessionInit>();
}

} // namespace app::ua
