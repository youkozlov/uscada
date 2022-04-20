#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include <vector>
#include <memory>

namespace app
{

class ModbusClient;
class ModbusServer;
struct ModbusInitReq;
struct ModbusReleaseReq;
struct ModbusConfigReq;
struct ModbusDataReq;
struct ModbusAduRsp;

class Modbus : public reactor::ComponentBase<CompIds::modbus>
{
public:
    explicit Modbus(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(ModbusInitReq const&);
    void receive(ModbusConfigReq const&);
    void receive(ModbusDataReq const&);
    void receive(ModbusAduRsp const&);
    void receive(ModbusReleaseReq const&);

private:
    void registerComponent();

    std::vector<std::unique_ptr<ModbusClient>> clients;
    std::unique_ptr<ModbusServer> server;
};

} // namespace app
