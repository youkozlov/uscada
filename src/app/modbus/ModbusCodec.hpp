#pragma once

#include "ModbusDefs.hpp"
#include "PduBuffer.hpp"

namespace app::modbus
{

class ModbusCodec
{
public:
    explicit ModbusCodec(PduBuffer&);

    bool encode(ModbusTcpAdu const&);

    bool encode(ModbusTcpAdu const&, void const*, unsigned);

    bool encode(ModbusTcpAdu const&, ModbusErorr);

    bool decode(ModbusTcpAdu&);

private:
    PduBuffer& buf;
};

} // namespace app::modbus
