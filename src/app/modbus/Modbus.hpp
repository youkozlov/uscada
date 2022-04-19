#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include <memory>

namespace app
{

class ModbusSession;
struct ModbusInitReq;
struct ModbusConfigReq;
struct ModbusDataReq;

class Modbus : public reactor::ComponentBase<CompIds::modbus>
{
public:
    explicit Modbus(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(ModbusInitReq const&);
    void receive(ModbusConfigReq const&);
    void receive(ModbusDataReq const&);

private:
    void registerComponent();

    std::unique_ptr<ModbusSession> session;
};

} // namespace app
