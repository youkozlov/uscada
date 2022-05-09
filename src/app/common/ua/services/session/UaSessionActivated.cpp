#include "UaSessionActivated.hpp"
#include "UaSessionInit.hpp"
#include "UaSession.hpp"

namespace app::ua
{

void UaSessionActivated::onClose(UaSession& fsm, UaCloseSessionReq const& req, UaServiceHandler handler)
{
    fsm.close(req, handler);
    fsm.transit<UaSessionInit>();
}

} // namespace app::ua
