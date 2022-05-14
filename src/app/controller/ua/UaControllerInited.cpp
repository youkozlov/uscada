#include "UaControllerInited.hpp"
#include "UaController.hpp"

namespace app::controller
{

void UaControllerInited::onReceive(UaController& fsm, MsgUaSecureChannelInitRsp const& msg)
{
    fsm.receive(msg);
}

void UaControllerInited::onReceive(UaController& fsm, MsgUaTransportInitRsp const& msg)
{
    fsm.receive(msg);
}

void UaControllerInited::onReceive(UaController& fsm, MsgUaServiceInitRsp const& msg)
{
    fsm.receive(msg);
}

void UaControllerInited::onReceive(UaController& fsm, MsgControllerStopReq const& msg)
{
    fsm.receive(msg);
}

} // namespace app::controller
