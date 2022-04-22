#pragma once

#include <vector>
#include <queue>
#include <memory>

namespace app::modbus
{

class ModbusSession;
class ModbusSessionHandler;

class ModbusSessionPool
{
public:
    explicit ModbusSessionPool(ModbusSessionHandler&);

    ~ModbusSessionPool();

    bool alloc(int&);

    void free(int);

    ModbusSession& get(int) const;

private:
    static constexpr int capacity = 256;

    std::vector<std::unique_ptr<ModbusSession>> sessions;
    std::queue<int> ids;
};

} // namespace app::modbus
