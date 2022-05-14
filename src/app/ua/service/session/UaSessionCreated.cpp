#include "UaSessionCreated.hpp"
#include "UaSessionActivated.hpp"
#include "UaSessionInit.hpp"
#include "UaSession.hpp"

namespace app::ua::service
{

void UaSessionCreated::onReceive(UaSession& fsm, UaEncodedMessageHdr const& hdr, UaActivateSessionReq const& req)
{
    fsm.receive(hdr, req);
    fsm.transit<UaSessionActivated>();
}

void UaSessionCreated::onReceive(UaSession& fsm, UaEncodedMessageHdr const& hdr, UaCloseSessionReq const& req)
{
    fsm.receive(hdr, req);
    fsm.transit<UaSessionInit>();
}

} // namespace app::ua::service
