#include "Controller.hpp"

#include "Logger.hpp"

#include "MsgStore.hpp"
#include "ControllerStartReq.hpp"
#include "ControllerStopReq.hpp"
#include "ConnectorInitReq.hpp"
#include "ConnectorInitRsp.hpp"
#include "DetectorInitReq.hpp"
#include "DetectorInitRsp.hpp"
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
#include <chrono>
#include <thread>

namespace app::controller
{

Controller::Controller(reactor::SenderInterface& sender, reactor::ReactorInterface& receiver)
    : ComponentBase(sender, receiver)
{
    registerComponent();

    for (unsigned i = 0; i < serverRegs.size(); ++i)
    {
        serverRegs[i] = i;
    }
}

void Controller::registerComponent()
{
    getReactor().registerHandlers
    ({
          { ControllerStartReq::msgId(), [this](auto const& msg){ receive(static_cast<ControllerStartReq const&>(msg)); }}
        , { ControllerStopReq::msgId(), [this](auto const& msg){ receive(static_cast<ControllerStopReq const&>(msg)); }}
        , { ConnectorInitRsp::msgId(), [this](auto const& msg){ receive(static_cast<ConnectorInitRsp const&>(msg)); }}
        , { DetectorInitRsp::msgId(), [this](auto const& msg){ receive(static_cast<DetectorInitRsp const&>(msg)); }}
        , { ModbusInitRsp::msgId(), [this](auto const& msg){ receive(static_cast<ModbusInitRsp const&>(msg)); }}
        , { ModbusReleaseRsp::msgId(), [this](auto const& msg){ receive(static_cast<ModbusReleaseRsp const&>(msg)); }}
        , { ModbusConfigRsp::msgId(), [this](auto const& msg){ receive(static_cast<ModbusConfigRsp const&>(msg)); }}
        , { ModbusClientAduRsp::msgId(), [this](auto const& msg){ receive(static_cast<ModbusClientAduRsp const&>(msg)); }}
        , { ModbusAduReq::msgId(), [this](auto const& msg){ receive(static_cast<ModbusAduReq const&>(msg)); }}
    });
}

void Controller::receive(ControllerStartReq const&)
{
    LM(CTRL, LD, "ControllerStartReq received");

    ConnectorInitReq req;
    getSender().send(req);

    ModbusInitReq modbusReq;
    modbusReq.maxNumServers = 2;
    modbusReq.maxNumClients = 8;
    getSender().send(modbusReq);
}

void Controller::receive(ControllerStopReq const&)
{
    LM(CTRL, LD, "ControllerStopReq received");

    ModbusReleaseReq req;
    getSender().send(req);
}

void Controller::receive(ConnectorInitRsp const&)
{
    LM(CTRL, LD, "ConnectorInitRsp received");
}

void Controller::receive(DetectorInitRsp const&)
{
    LM(CTRL, LD, "DetectorInitRsp received");
}

void Controller::receive(ModbusInitRsp const&)
{
    LM(CTRL, LD, "ModbusInitRsp received");

    reactor::MsgStore<ModbusConfigReq> msgEv;
    ModbusConfigReq& req = msgEv.getMsg();

    EntityId id = 0;
    req.numItems = 0;
    for (unsigned i = 0; i < 2u; ++i)
    {
        ModbusConfig& item = req.items[req.numItems++];
        item.id = id++;
        item.mode = ModbusConfig::Mode::client;
    }

    id = 0;
    for (unsigned i = 0; i < 1u; ++i)
    {
        ModbusConfig& item = req.items[req.numItems++];
        item.id = id++;
        item.mode = ModbusConfig::Mode::server;
    }

    getSender().send(req);
}

void Controller::receive(ModbusReleaseRsp const&)
{
    LM(CTRL, LD, "ModbusReleaseRsp received");
}

void Controller::receive(ModbusConfigRsp const&)
{
    LM(CTRL, LD, "ModbusConfigRsp received");

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);

    for (size_t i = 0; i < 6; i++)
    {
        reactor::MsgStore<ModbusClientAduReq> msgEv;
        ModbusClientAduReq& req = msgEv.getMsg();

        req.clientId = i % 2;
        req.addr = 1;
        req.func = 0x4;
        req.startReg = 5;
        req.numRegs = 2 * i;
        req.numBytes = 0;

        getSender().send(req);
    }
}

void Controller::receive(ModbusClientAduRsp const&)
{
    LM(CTRL, LD, "ModbusClientAduRsp received");
}

void Controller::receive(ModbusAduReq const& req)
{
    LM(CTRL, LD, "ModbusAduReq: serverId=%d sessionId=%d aduId=%d startReg=%u numRegs=%u numBytes=%u"
        , req.serverId, req.sessionId, req.aduId, req.startReg, req.numRegs, req.numBytes);

    reactor::MsgStore<ModbusAduRsp> msgEv;
    ModbusAduRsp& rsp = msgEv.getMsg();

    rsp.serverId = req.serverId;
    rsp.sessionId = req.sessionId;
    rsp.aduId = req.aduId;
    rsp.status = MsgStatus::success;
    rsp.numBytes = req.numRegs * 2;
    std::memcpy(&rsp.data[0], &serverRegs[req.startReg], rsp.numBytes);
    getSender().send(rsp);
}

} // namespace app::controller
