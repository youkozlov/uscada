#include "UaControllerInit.hpp"
#include "UaControllerInited.hpp"
#include "UaController.hpp"

namespace app::controller
{

void UaControllerInit::onReceive(UaController& fsm, MsgControllerStartReq const& msg)
{
    fsm.receive(msg);
    fsm.transit<UaControllerInited>();
}

} // namespace app::controller
