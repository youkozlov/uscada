#pragma once

#include <cstdint>

namespace app
{

enum class ModbusFunction : std::uint8_t
{
      readCoilStatus = 0x1
    , readDiscreteInputs = 0x2
    , readHoldingRegisters = 0x3
    , readInputRegisters = 0x4
    , forceSingleCoil = 0x5
    , presetSingleRegister = 0x6
    , presetMultipleRegisters = 0x10
    , modbusError = 0x8f
};

inline std::uint8_t toUint8(ModbusFunction val)
{
    return static_cast<std::uint8_t>(val);
}

inline char const* toString(ModbusFunction val)
{
    switch (val)
    {
    case ModbusFunction::readCoilStatus:             return "readCoilStatus";
    case ModbusFunction::readDiscreteInputs:         return "readDiscreteInputs";
    case ModbusFunction::readHoldingRegisters:       return "readHoldingRegisters";
    case ModbusFunction::readInputRegisters:         return "readInputRegisters";
    case ModbusFunction::forceSingleCoil:            return "forceSingleCoil";
    case ModbusFunction::presetSingleRegister:       return "presetSingleRegister";
    case ModbusFunction::presetMultipleRegisters:    return "presetMultipleRegisters";
    case ModbusFunction::modbusError:                return "modbusError";
    }
    return "Unexpected";
}

} // namespace app
