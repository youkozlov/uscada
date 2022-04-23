#pragma once

#include <vector>
#include <queue>
#include <memory>

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
    std::vector<std::unique_ptr<ModbusSession>> sessions;
    std::queue<ModbusSession::Uid> ids;
};

} // namespace app::modbus
