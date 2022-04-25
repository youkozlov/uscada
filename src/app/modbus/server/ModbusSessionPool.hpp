#pragma once

#include <vector>
#include <memory>

#include "Queue.hpp"
#include "ModbusSession.hpp"

namespace app::modbus
{

class ModbusSession;
class ModbusSessionHandler;

class ModbusSessionPool
{
public:
    explicit ModbusSessionPool(ModbusSessionHandler&, ModbusSession::Uid);

    ~ModbusSessionPool();

    bool alloc(ModbusSession::Uid&);

    void free(ModbusSession::Uid);

    ModbusSession& get(ModbusSession::Uid) const;

private:
    Queue<ModbusSession::Uid> ids;
    std::vector<std::unique_ptr<ModbusSession>> sessions;
};

} // namespace app::modbus
