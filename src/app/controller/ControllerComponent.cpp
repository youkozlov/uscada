#include "ControllerComponent.hpp"
#include "Logger.hpp"

namespace app::controller
{

ControllerComponent::ControllerComponent(reactor::SenderInterface& sender, reactor::ReactorInterface& reactor_)
    : ComponentBase(sender, reactor_)
    , sender(*this)
    , reactor(reactor_)
{
    registerComponent();
}

void ControllerComponent::registerComponent()
{
    getReactor().registerHandlers
    ({
          { MsgControllerStartReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgControllerStartReq const&>(msg)); }}
        , { MsgControllerStopReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgControllerStopReq const&>(msg)); }}
        , { MsgModbusInitRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusInitRsp const&>(msg)); }}
        , { MsgModbusReleaseRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusReleaseRsp const&>(msg)); }}
        , { MsgModbusConfigRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusConfigRsp const&>(msg)); }}
        , { MsgModbusClientAduRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusClientAduRsp const&>(msg)); }}
        , { MsgModbusAduReq::msgId(), [this](auto const& msg){ receive(static_cast<MsgModbusAduReq const&>(msg)); }}
        , { MsgUaSecureChannelInitRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaSecureChannelInitRsp const&>(msg)); }}
        , { MsgUaSecureChannelConfigRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaSecureChannelConfigRsp const&>(msg)); }}
        , { MsgUaSecureChannelReleaseRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaSecureChannelReleaseRsp const&>(msg)); }}
        , { MsgUaTransportInitRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaTransportInitRsp const&>(msg)); }}
        , { MsgUaTransportConfigRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaTransportConfigRsp const&>(msg)); }}
        , { MsgUaTransportReleaseRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaTransportReleaseRsp const&>(msg)); }}
        , { MsgUaServiceInitRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaServiceInitRsp const&>(msg)); }}
        , { MsgUaServiceConfigRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaServiceConfigRsp const&>(msg)); }}
        , { MsgUaServiceReleaseRsp::msgId(), [this](auto const& msg){ receive(static_cast<MsgUaServiceReleaseRsp const&>(msg)); }}
    });
}

void ControllerComponent::receive(MsgControllerStartReq const& req)
{
    LM(CTRL, LD, "ControllerStartReq received");

    modbus = std::make_unique<ModbusTestController>();
    modbus->receive(req);

    opcUa = std::make_unique<UaController>();
    opcUa->getState().onReceive(*opcUa, req);
}

void ControllerComponent::receive(MsgControllerStopReq const& req)
{
    LM(CTRL, LD, "ControllerStopReq received");
    modbus->receive(req);
    modbus.reset();
    opcUa->getState().onReceive(*opcUa, req);
    opcUa.reset();
}

void ControllerComponent::receive(MsgModbusInitRsp const& rsp)
{
    LM(CTRL, LD, "ModbusInitRsp received");
    if (modbus)
        modbus->receive(rsp);
}

void ControllerComponent::receive(MsgModbusReleaseRsp const& rsp)
{
    LM(CTRL, LD, "ModbusReleaseRsp received");
    if (modbus)
        modbus->receive(rsp);
}

void ControllerComponent::receive(MsgModbusConfigRsp const& rsp)
{
    LM(CTRL, LD, "ModbusConfigRsp received");
    if (modbus)
        modbus->receive(rsp);
}

void ControllerComponent::receive(MsgModbusClientAduRsp const& rsp)
{
    LM(CTRL, LD, "ModbusClientAduRsp received");
    if (modbus)
        modbus->receive(rsp);
}

void ControllerComponent::receive(MsgModbusAduReq const& req)
{
    LM(CTRL, LD, "ModbusAduReq received");
    if (modbus)
        modbus->receive(req);
}

void ControllerComponent::receive(MsgUaSecureChannelInitRsp const& msg)
{
    LM(CTRL, LD, "UaSecureChannelInitRsp received");

    if (opcUa)
        opcUa->getState().onReceive(*opcUa, msg);
}

void ControllerComponent::receive(MsgUaSecureChannelConfigRsp const& msg)
{
    LM(CTRL, LD, "UaSecureChannelConfigRsp received");

    if (opcUa)
        opcUa->getState().onReceive(*opcUa, msg);
}

void ControllerComponent::receive(MsgUaSecureChannelReleaseRsp const& msg)
{
    LM(CTRL, LD, "UaSecureChannelReleaseRsp received");

    if (opcUa)
        opcUa->getState().onReceive(*opcUa, msg);
}

void ControllerComponent::receive(MsgUaTransportInitRsp const& msg)
{
    LM(CTRL, LD, "UaTransportInitRsp received");

    if (opcUa)
        opcUa->getState().onReceive(*opcUa, msg);
}

void ControllerComponent::receive(MsgUaTransportConfigRsp const& msg)
{
    LM(CTRL, LD, "UaTransportConfigRsp received");

    if (opcUa)
        opcUa->getState().onReceive(*opcUa, msg);
}

void ControllerComponent::receive(MsgUaTransportReleaseRsp const& msg)
{
    LM(CTRL, LD, "UaTransportReleaseRsp received");

    if (opcUa)
        opcUa->getState().onReceive(*opcUa, msg);
}

void ControllerComponent::receive(MsgUaServiceInitRsp const& msg)
{
    LM(CTRL, LD, "UaServiceInitRsp received");

    if (opcUa)
        opcUa->getState().onReceive(*opcUa, msg);
}

void ControllerComponent::receive(MsgUaServiceConfigRsp const& msg)
{
    LM(CTRL, LD, "UaServiceConfigRsp received");

    if (opcUa)
        opcUa->getState().onReceive(*opcUa, msg);
}

void ControllerComponent::receive(MsgUaServiceReleaseRsp const& msg)
{
    LM(CTRL, LD, "UaServiceReleaseRsp received");

    if (opcUa)
        opcUa->getState().onReceive(*opcUa, msg);
}


} // namespace app::controller
