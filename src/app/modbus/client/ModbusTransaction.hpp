#pragma once

#include <cstdint>
#include "EntityId.hpp"

namespace app::modbus
{

using TransactId = unsigned;

struct ModbusTransaction
{
    app::EntityId   clientId;
    TransactId      transactId;
    uint16_t        func;
    uint16_t        addr;
    uint16_t        startReg;
    uint16_t        numRegs;
    uint16_t        numBytes{};
    void const*     data{};
};

}