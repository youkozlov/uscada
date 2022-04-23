#include "ModbusCodec.hpp"

namespace app::modbus
{

ModbusCodec::ModbusCodec(PduBuffer& buf_)
    : buf(buf_)
{
}

unsigned ModbusCodec::pduLen() const
{
    unsigned hh = buf.begin()[pduLenOffset + 0];
    unsigned ll = buf.begin()[pduLenOffset + 1];
    return (hh << 8) | ll;
}

bool ModbusCodec::isPduHdrReceived() const
{
    return buf.size() >= pduHdrLen;
}

bool ModbusCodec::isPduReceived() const
{
    return buf.size() >= pduLen();
}

bool ModbusCodec::isPduValid() const
{
    return pduLen() < maxPduLen;
}

bool ModbusCodec::encode(ModbusTcpAdu const& adu)
{
    buf.writeBe(adu.transactionId);
    buf.writeBe(adu.protocolId);
    buf.writeBe(1 + 1 + 2 + 2);
    buf.write(adu.slaveAddr);
    buf.write(adu.func);
    buf.writeBe(adu.startReg);
    buf.writeBe(adu.numRegs);

    return true;
}

bool ModbusCodec::encode(ModbusTcpAdu const& adu, void const* data, unsigned len)
{
    buf.writeBe(adu.transactionId);
    buf.writeBe(adu.protocolId);
    buf.writeBe(1 + 1 + 1 + len);
    buf.write(adu.slaveAddr);
    buf.write(adu.func);
    buf.write(len);
    uint16_t const* regs = static_cast<uint16_t const*>(data);
    for (unsigned i = 0; i < len; i += 2)
    {
        buf.writeBe(*regs++);
    }
    return true;
}

bool ModbusCodec::decode(ModbusTcpAdu& adu, uint8_t* data, uint16_t& numBytes)
{
    adu.transactionId = buf.readBe();
    adu.protocolId = buf.readBe();
    adu.pktLen = buf.readBe();
    adu.slaveAddr = buf.read();
    adu.func = buf.read();

    numBytes = 0;

    switch (adu.func)
    {
    case modbusErrorFunc:
    {
        adu.err = buf.read();
    }
    break;
    case readInputRegistersFunc:
    {
        numBytes = buf.read();
        for (unsigned i = 0; i < numBytes; i += 2)
        {
            data[i + 1] = buf.read();
            data[i + 0] = buf.read();
        }
    }
    break;
    default:
    {
        return false;
    }
    break;
    }
    return true;
}

bool ModbusCodec::encode(ModbusTcpAdu const& adu, ModbusErorr err)
{
    buf.writeBe(adu.transactionId);
    buf.writeBe(adu.protocolId);
    buf.writeBe(1 + 1 + 1);
    buf.write(adu.slaveAddr);
    buf.write(modbusErrorFunc);
    buf.write(err);

    return true;
}

bool ModbusCodec::decode(ModbusTcpAdu& adu)
{
    adu.transactionId = buf.readBe();
    adu.protocolId = buf.readBe();
    adu.pktLen = buf.readBe();
    adu.slaveAddr = buf.read();
    adu.func = buf.read();

    return true;
}

} // namespace app::modbus
