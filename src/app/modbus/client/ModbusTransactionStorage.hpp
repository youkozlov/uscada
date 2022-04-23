#pragma once

#include <cstdint>
#include <vector>
#include "Queue.hpp"
#include "ModbusTransaction.hpp"

namespace app::modbus
{

class ModbusTransactionStorage
{
public:
    ModbusTransactionStorage();

    ~ModbusTransactionStorage();

    bool push(ModbusTransaction const&);

    ModbusTransaction const& front();

    void pop();

    bool empty() const;

private:
    static constexpr unsigned capacity = 64;
    static constexpr unsigned transactionNumBytes = 256;
    static constexpr unsigned bufferSize = capacity * transactionNumBytes;

    app::Queue<unsigned> freeIds;
    app::Queue<unsigned> busyIds;
    std::vector<ModbusTransaction> pool;
    char buffer[bufferSize];
};

} // namespace app::modbus
