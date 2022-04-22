#include "ModbusCodec.hpp"

namespace app::modbus
{

ModbusCodec::ModbusCodec(PduBuffer& buf_)
    : buf(buf_)
{
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

bool ModbusCodec::encode(ModbusTcpAdu const& adu, ModbusErorr err)
{
    constexpr int MB_ERR = 0x8f;

    buf.writeBe(adu.transactionId);
    buf.writeBe(adu.protocolId);
    buf.writeBe(1 + 1 + 1);
    buf.write(adu.slaveAddr);
    buf.write(MB_ERR);
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
