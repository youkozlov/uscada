#include "UaSessionInit.hpp"
#include "UaSessionCreated.hpp"
#include "UaSession.hpp"

namespace app::ua
{

void UaSessionInit::onEnter(UaSession& fsm)
{
    fsm.release();
}

void UaSessionInit::onCreate(UaSession& fsm, UaCreateSessionReq const& req, UaServiceHandler handler)
{
    fsm.create(req, handler);
    fsm.transit<UaSessionCreated>();
}

} // namespace app::ua
