#include "UaSessionActivated.hpp"
#include "UaSessionInit.hpp"
#include "UaSession.hpp"

namespace app::ua::service
{

void UaSessionActivated::onReceive(UaSession& fsm, UaEncodedMessageHdr const& hdr, UaActivateSessionReq const& req)
{
    fsm.receive(hdr, req);
}

void UaSessionActivated::onReceive(UaSession& fsm, UaEncodedMessageHdr const& hdr, UaCloseSessionReq const& req)
{
    fsm.receive(hdr, req);
    fsm.transit<UaSessionInit>();
}

void UaSessionActivated::onReceive(UaSession& fsm, UaEncodedMessageHdr const& hdr, UaServiceHandler const& handler)
{
    fsm.receive(hdr, handler);
}

} // namespace app::ua::service
