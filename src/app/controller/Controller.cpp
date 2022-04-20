#include "Controller.hpp"

#include "Logger.hpp"

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
#include "ModbusAduReq.hpp"
#include "ModbusAduRsp.hpp"


namespace app
{

Controller::Controller(reactor::SenderInterface& sender, reactor::ReactorInterface& receiver)
    : ComponentBase(sender, receiver)
{
    registerComponent();
}

void Controller::registerComponent()
{
    getReactor().registerHandler(
          ControllerStartReq::msgId
        , [this](auto const& msg){ receive(static_cast<ControllerStartReq const&>(msg)); }
    );
    getReactor().registerHandler(
          ControllerStopReq::msgId
        , [this](auto const& msg){ receive(static_cast<ControllerStopReq const&>(msg)); }
    );
    getReactor().registerHandler(
          ConnectorInitRsp::msgId
        , [this](auto const& msg){ receive(static_cast<ConnectorInitRsp const&>(msg)); }
    );
    getReactor().registerHandler(
          DetectorInitRsp::msgId
        , [this](auto const& msg){ receive(static_cast<DetectorInitRsp const&>(msg)); }
    );
    getReactor().registerHandler(
          ModbusInitRsp::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusInitRsp const&>(msg)); }
    );
    getReactor().registerHandler(
          ModbusReleaseRsp::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusReleaseRsp const&>(msg)); }
    );
    getReactor().registerHandler(
          ModbusAduReq::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusAduReq const&>(msg)); }
    );
}

void Controller::receive(ControllerStartReq const&)
{
    LM(CTRL, LD, "ControllerStartReq received");

    ConnectorInitReq req;
    getSender().send(req);

    ModbusInitReq modbusReq;
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

    ModbusConfigReq req;
    getSender().send(req);
}

void Controller::receive(ModbusReleaseRsp const&)
{
    LM(CTRL, LD, "ModbusReleaseRsp received");
}

void Controller::receive(ModbusAduReq const& req)
{
    LM(CTRL, LD, "ModbusAduReq received");

    ModbusAduRsp rsp;
    rsp.serverId = req.serverId;
    rsp.sessionId = req.sessionId;
    rsp.aduId = req.aduId;
    rsp.status = MsgStatus::success;
    rsp.numItems = req.numItems;

    getSender().send(rsp);
}

} // namespace app
