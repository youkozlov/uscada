#pragma once

#include <cstdint>
#include "EntityId.hpp"
#include "ModbusDefs.hpp"
#include "ModbusFunction.hpp"
#include "ModbusError.hpp"

namespace app::modbus
{

using TransactId = unsigned;

struct AduRespond
{
    TransactId      transactId;
    ModbusFunction  func;
    uint16_t        addr;
    ModbusError     error;
    uint16_t        startItem;
    uint16_t        numItems;
    uint16_t        numBytes{};
    uint8_t         data[maxAduLen];
};

}