#include "UaController.hpp"
#include "ControllerReactor.hpp"
#include "ControllerSender.hpp"
#include "UaControllerInit.hpp"

namespace app::controller
{

UaController::UaController()
    : FsmBase(&app::getSingleton<UaControllerInit>(), "UaController")
{
}

UaController::~UaController()
{
}

/*
void UaController::start()
{
    reactor::LinkAddr addr;
    addr.data[0] = 0x7f;
    addr.data[1] = 0x0;
    addr.data[2] = 0x0;
    addr.data[3] = 0x1;
    addr.data[4] = 0x11;
    addr.data[5] = 0x11;
}
*/

void UaController::receive(MsgControllerStartReq const&)
{
    reactor::MsgStore<MsgUaSecureChannelInitReq> scMsgStore;
    Sender::sendMsg(scMsgStore);

    reactor::MsgStore<MsgUaTransportInitReq> tlMsgStore;
    Sender::sendMsg(tlMsgStore);

    reactor::MsgStore<MsgUaServiceInitReq> srvMsgStore;
    Sender::sendMsg(srvMsgStore);
}

void UaController::receive(MsgControllerStopReq const&)
{
    reactor::MsgStore<MsgUaSecureChannelReleaseReq> scMsgStore;
    Sender::sendMsg(scMsgStore);

    reactor::MsgStore<MsgUaTransportReleaseReq> tlMsgStore;
    Sender::sendMsg(tlMsgStore);

    reactor::MsgStore<MsgUaServiceReleaseReq> srvMsgStore;
    Sender::sendMsg(srvMsgStore);
}

void UaController::receive(MsgUaSecureChannelInitRsp const&)
{
    reactor::MsgStore<MsgUaSecureChannelConfigReq> msgStore;
    Sender::sendMsg(msgStore);
}

void UaController::receive(MsgUaSecureChannelConfigRsp const&)
{
}

void UaController::receive(MsgUaSecureChannelReleaseRsp const&)
{

}

void UaController::receive(MsgUaTransportInitRsp const&)
{
    reactor::MsgStore<MsgUaTransportConfigReq> msgStore;
    auto& msg = msgStore.getMsg();
    msg.addr.data[0] = 0x7f;
    msg.addr.data[1] = 0x0;
    msg.addr.data[2] = 0x0;
    msg.addr.data[3] = 0x1;
    msg.addr.data[4] = 0x11;
    msg.addr.data[5] = 0x11;
    Sender::sendMsg(msgStore);
}

void UaController::receive(MsgUaTransportConfigRsp const&)
{
}

void UaController::receive(MsgUaTransportReleaseRsp const&)
{
}

void UaController::receive(MsgUaServiceInitRsp const&)
{
    reactor::MsgStore<MsgUaServiceConfigReq> msgStore;
    Sender::sendMsg(msgStore);
}

void UaController::receive(MsgUaServiceConfigRsp const&)
{
}

void UaController::receive(MsgUaServiceReleaseRsp const&)
{

}


} // namespace app::controller
