#pragma once

#include <vector>
#include <queue>
#include <memory>

namespace app
{

class ModbusSession;
class ModbusServer;

class ModbusSessionPool
{
public:
    explicit ModbusSessionPool(ModbusServer&);

    ~ModbusSessionPool();

    bool alloc(int&);

    void free(int);

    ModbusSession& get(int) const;

private:
    static constexpr int capacity = 256;

    std::vector<std::unique_ptr<ModbusSession>> sessions;
    std::queue<int> ids;
};

} // namespace app
