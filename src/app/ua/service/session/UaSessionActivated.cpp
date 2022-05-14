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

} // namespace app::ua::service
