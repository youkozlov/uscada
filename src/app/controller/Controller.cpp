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
}

void Controller::receive(ControllerStartReq const&)
{
    LM(CTRL, LD, "ControllerStartReq received");

    ConnectorInitReq req;
    getSender().send(req);
}

void Controller::receive(ControllerStopReq const&)
{
}

void Controller::receive(ConnectorInitRsp const&)
{
    LM(CTRL, LD, "ConnectorInitRsp received");

    ModbusInitReq req;
    getSender().send(req);
}

void Controller::receive(DetectorInitRsp const&)
{
    LM(CTRL, LD, "DetectorInitRsp received");
}

void Controller::receive(ModbusInitRsp const&)
{
    LM(CTRL, LD, "ModbusInitRsp received");
}

} // namespace app
