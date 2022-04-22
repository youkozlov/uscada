#pragma once

#include <cstdint>

namespace app::modbus
{

enum ModbusErorr
{
    NoError = 0,
    IllegalFunction = 1,
    IllegalDataAddress = 2,
    IllegalDataValue = 3,
    SlaveDeviceFailure = 4,
    Acknowledge = 5,
    SlaveDeviceBusy = 6,
    NegativeAcknowledge = 7,
    MemoryParityError = 8,
    GatewayPathUnavailable = 10,
    GatewayTargetDeviceFailedtoRespond = 11
};

struct ModbusTcpAdu
{
    uint16_t transactionId;
    uint16_t protocolId;
    uint16_t pktLen;
    uint16_t startReg;
    uint16_t numRegs;
    uint8_t  slaveAddr;
    uint8_t  func;

    bool     decoded;

    void reset()
    {
        decoded = false;
    }
    unsigned aduLen() const
    {
        return pktLen + 6;
    }
    unsigned aduHdrLen() const
    {
        return 8;
    }
    bool isDecoded() const
    {
        return decoded;
    }
    bool isValid() const
    {
        return pktLen > 2 && pktLen < 256;
    }
    bool isRead() const
    {
        return func == 0x3 || func == 0x4;
    }
};

struct ModbusReq
{
    uint8_t  slaveAddr;
    uint8_t  fc;
    uint16_t startReg;
    uint16_t numRegs;
};

} // namespace app::modbus
