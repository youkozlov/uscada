#include "UaSessionInit.hpp"
#include "UaSessionCreated.hpp"
#include "UaSession.hpp"

namespace app::ua::service
{

void UaSessionInit::onEnter(UaSession& fsm)
{
    fsm.release();
}

void UaSessionInit::onReceive(UaSession& fsm, UaEncodedMessageHdr const& hdr, UaCreateSessionReq const& req)
{
    fsm.receive(hdr, req);
    fsm.transit<UaSessionCreated>();
}

} // namespace app::ua::service
