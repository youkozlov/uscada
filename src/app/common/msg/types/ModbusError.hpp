#pragma once

namespace app
{

enum class ModbusError : std::uint8_t
{
      noerror = 0
    , illegalFunction = 1
    , illegalDataAddress = 2
    , illegalDataValue = 3
    , serverDeviceFailure = 4
    , acknowledge = 5
    , serverDeviceBusy = 6
    , negativeAcknowledge = 7
    , memoryParityError = 8
    , gatewayPathUnavailable = 10
    , gatewayTargetDeviceFailed = 11
    , unexpected = 255
};

inline std::uint8_t toUint8(ModbusError val)
{
    switch (val)
    {
    case ModbusError::noerror:                      return 0;
    case ModbusError::illegalFunction:              return 1;
    case ModbusError::illegalDataAddress:           return 2;
    case ModbusError::illegalDataValue:             return 3;
    case ModbusError::serverDeviceFailure:          return 4;
    case ModbusError::acknowledge:                  return 5;
    case ModbusError::serverDeviceBusy:             return 6;
    case ModbusError::negativeAcknowledge:          return 7;
    case ModbusError::memoryParityError:            return 8;
    case ModbusError::gatewayPathUnavailable:       return 10;
    case ModbusError::gatewayTargetDeviceFailed:    return 11;
    case ModbusError::unexpected:                   return 255;
    }
    return 255;
}

inline char const* toString(ModbusError val)
{
    switch (val)
    {
    case ModbusError::noerror:                      return "noerror";
    case ModbusError::illegalFunction:              return "illegalFunction";
    case ModbusError::illegalDataAddress:           return "illegalDataAddress";
    case ModbusError::illegalDataValue:             return "illegalDataValue";
    case ModbusError::serverDeviceFailure:          return "serverDeviceFailure";
    case ModbusError::acknowledge:                  return "acknowledge";
    case ModbusError::serverDeviceBusy:             return "serverDeviceBusy";
    case ModbusError::negativeAcknowledge:          return "negativeAcknowledge";
    case ModbusError::memoryParityError:            return "memoryParityError";
    case ModbusError::gatewayPathUnavailable:       return "gatewayPathUnavailable";
    case ModbusError::gatewayTargetDeviceFailed:    return "gatewayTargetDeviceFailed";
    case ModbusError::unexpected:                   return "unexpected";
    }
    return "unexpected";
}

} // namespace app
