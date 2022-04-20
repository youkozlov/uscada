#pragma once

#include <vector>
#include <queue>

#include "ModbusDefs.hpp"

namespace app
{

class ModbusAduPool
{
public:
    explicit ModbusAduPool();

    ~ModbusAduPool();

    bool alloc(int&);

    void free(int);

    ModbusTcpAdu& get(int);

private:
    static constexpr int capacity = 256;

    std::vector<ModbusTcpAdu> adus;
    std::queue<int> ids;
};

} // namespace app
