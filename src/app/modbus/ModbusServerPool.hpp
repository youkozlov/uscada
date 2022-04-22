#pragma once

#include <vector>
#include <queue>

namespace app::modbus
{

class ModbusServer;

class ModbusServerPool
{
public:
    explicit ModbusServerPool();

    ~ModbusServerPool();

    bool alloc(int&);

    void free(int);

    ModbusServer& get(int) const;

private:
    static constexpr int capacity = 256;

    std::vector<ModbusServer> pool;
    std::queue<int> ids;
};

} // namespace app::modbus
