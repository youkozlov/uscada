#pragma once

#include <cstdint>
#include "EntityId.hpp"
#include "TransactId.hpp"
#include "ModbusFunction.hpp"

namespace app::modbus
{

using TransactId = unsigned;

struct AduRequest
{
    AduRequest() = default;
    AduRequest(std::uint8_t* dataInit)
        : data(dataInit)
    {}
    EntityId        clientId;
    TransactId      transactId;
    ModbusFunction  func;
    uint16_t        addr;
    uint16_t        startItem;
    uint16_t        numItems;
    uint16_t        numBytes{};
    uint8_t*        data{};
};

}