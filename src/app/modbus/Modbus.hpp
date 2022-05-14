#pragma once

#include <vector>
#include <memory>

#include "MsgModbusConfigReq.hpp"
#include "MsgModbusClientAduReq.hpp"
#include "MsgModbusAduRsp.hpp"

#include "ReactorInterface.hpp"
#include "ModbusServer.hpp"
#include "ModbusClient.hpp"

namespace app::modbus
{

class Modbus
{
public:
    struct Init
    {
        std::size_t maxNumServers;
        std::size_t maxNumClients;
    };

    explicit Modbus(Init const&);

    ~Modbus();

    void receive(MsgModbusConfigReq const&);
    void receive(MsgModbusClientAduReq const&);
    void receive(MsgModbusAduRsp const&);

private:
    std::vector<std::unique_ptr<ModbusServer>> servers;
    std::vector<std::unique_ptr<ModbusClient>> clients;
};

} // namespace app::modbus
