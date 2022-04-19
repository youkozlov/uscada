#include "Modbus.hpp"

#include "Logger.hpp"

#include "ModbusInitReq.hpp"
#include "ModbusInitRsp.hpp"
#include "ModbusConfigReq.hpp"
#include "ModbusConfigRsp.hpp"
#include "ModbusDataReq.hpp"
#include "ModbusDataInd.hpp"
#include "ModbusSession.hpp"

namespace app
{

Modbus::Modbus(reactor::SenderInterface& sender, reactor::ReactorInterface& receiver)
    : ComponentBase(sender, receiver)
{
    registerComponent();
}

void Modbus::registerComponent()
{
    getReactor().registerHandler(
          ModbusInitReq::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusInitReq const&>(msg)); }
    );
    getReactor().registerHandler(
          ModbusConfigReq::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusConfigReq const&>(msg)); }
    );
    getReactor().registerHandler(
          ModbusDataReq::msgId
        , [this](auto const& msg){ receive(static_cast<ModbusDataReq const&>(msg)); }
    );
}

void Modbus::receive(ModbusInitReq const&)
{
    LM(MODBUS, LD, "ModbusInitReq received");

    session = std::make_unique<ModbusSession>(getSender(), getReactor());

    session->connect();

    ModbusInitRsp rsp;
    getSender().send(rsp);
}

void Modbus::receive(ModbusConfigReq const&)
{
}

void Modbus::receive(ModbusDataReq const&)
{
}


} // namespace app
