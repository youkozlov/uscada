#pragma once

#include "ModbusDefs.hpp"
#include "PduBuffer.hpp"

namespace app::modbus
{

class ModbusCodec
{
public:
    explicit ModbusCodec(PduBuffer&);

    unsigned pduLen() const;

    bool isPduHdrReceived() const;

    bool isPduReceived() const;

    bool isPduValid() const;

    bool encode(ModbusTcpAdu const&);

    bool encode(ModbusTcpAdu const&, void const*, unsigned);

    bool decode(ModbusTcpAdu&, uint8_t*, uint16_t&);

    bool encode(ModbusTcpAdu const&, ModbusErorr);

    bool decode(ModbusTcpAdu&);

private:
    static constexpr unsigned pduLenOffset = 4;
    static constexpr unsigned pduHdrLen = 6;
    static constexpr unsigned maxPduLen = 256;

    static constexpr unsigned modbusErrorFunc = 0x8f;
    static constexpr unsigned readInputRegistersFunc = 0x4;

    PduBuffer& buf;
};

} // namespace app::modbus
