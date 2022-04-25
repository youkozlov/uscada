#pragma once

#include "ModbusDefs.hpp"
#include "PduBuffer.hpp"
#include "AduRequest.hpp"
#include "AduRespond.hpp"

namespace app::modbus
{

class ModbusCodec
{
public:
    explicit ModbusCodec(PduBuffer&);

    unsigned aduPktLen() const;

    unsigned pduLen(ModbusFunction, unsigned) const;

    bool isAduHdrReceived() const;

    bool isAduDataLenValid() const;

    bool isAduReceived() const;

    bool isAduValid() const;

    bool encode(AduRequest const&);

    bool decode(AduRequest&);

    bool encode(AduRespond const&);

    bool decode(AduRespond&);


private:
    static constexpr unsigned aduLenOffset = 4;
    static constexpr unsigned aduFuncCodeOffset = 7;
    static constexpr unsigned aduRspErrorCodeOffset = 8;
    static constexpr unsigned aduHdrLen = 6;

    PduBuffer& buf;
};

} // namespace app::modbus
