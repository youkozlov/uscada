#pragma once

#include "ModbusDefs.hpp"
#include "PduBuffer.hpp"

namespace app
{

class ModbusCodec
{
public:
    explicit ModbusCodec(PduBuffer&);

    bool encode(ModbusTcpAdu const&);

    bool decode(ModbusTcpAdu&);

private:
    PduBuffer& buf;
};

} // namespace app
