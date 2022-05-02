#include "ControllerComponent.hpp"

#include "ControllerStartReq.hpp"
#include "ControllerStopReq.hpp"
#include "ModbusInitReq.hpp"
#include "ModbusInitRsp.hpp"
#include "ModbusReleaseReq.hpp"
#include "ModbusReleaseRsp.hpp"
#include "ModbusConfigReq.hpp"
#include "ModbusConfigRsp.hpp"
#include "ModbusClientAduReq.hpp"
#include "ModbusClientAduRsp.hpp"
#include "ModbusAduReq.hpp"
#include "ModbusAduRsp.hpp"

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
          { ControllerStartReq::msgId(), [this](auto const& msg){ receive(static_cast<ControllerStartReq const&>(msg)); }}
        , { ControllerStopReq::msgId(), [this](auto const& msg){ receive(static_cast<ControllerStopReq const&>(msg)); }}
        , { ModbusInitRsp::msgId(), [this](auto const& msg){ receive(static_cast<ModbusInitRsp const&>(msg)); }}
        , { ModbusReleaseRsp::msgId(), [this](auto const& msg){ receive(static_cast<ModbusReleaseRsp const&>(msg)); }}
        , { ModbusConfigRsp::msgId(), [this](auto const& msg){ receive(static_cast<ModbusConfigRsp const&>(msg)); }}
        , { ModbusClientAduRsp::msgId(), [this](auto const& msg){ receive(static_cast<ModbusClientAduRsp const&>(msg)); }}
        , { ModbusAduReq::msgId(), [this](auto const& msg){ receive(static_cast<ModbusAduReq const&>(msg)); }}
    });
}

void ControllerComponent::receive(ControllerStartReq const& req)
{
    LM(CTRL, LD, "ControllerStartReq received");

    modbus = std::make_unique<ModbusTestController>();
    modbus->receive(req);
    opcUa = std::make_unique<OpcUaController>();
}

void ControllerComponent::receive(ControllerStopReq const& req)
{
    LM(CTRL, LD, "ControllerStopReq received");
    modbus->receive(req);
    modbus.reset();
    opcUa.reset();
}

void ControllerComponent::receive(ModbusInitRsp const& rsp)
{
    LM(CTRL, LD, "ModbusInitRsp received");
    if (modbus)
        modbus->receive(rsp);
}

void ControllerComponent::receive(ModbusReleaseRsp const& rsp)
{
    LM(CTRL, LD, "ModbusReleaseRsp received");
    if (modbus)
        modbus->receive(rsp);
}

void ControllerComponent::receive(ModbusConfigRsp const& rsp)
{
    LM(CTRL, LD, "ModbusConfigRsp received");
    if (modbus)
        modbus->receive(rsp);
}

void ControllerComponent::receive(ModbusClientAduRsp const& rsp)
{
    LM(CTRL, LD, "ModbusClientAduRsp received");
    if (modbus)
        modbus->receive(rsp);
}

void ControllerComponent::receive(ModbusAduReq const& req)
{
    LM(CTRL, LD, "ModbusAduReq received");
    if (modbus)
        modbus->receive(req);
}

} // namespace app::controller
