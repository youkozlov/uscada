#include "ModbusCodec.hpp"

namespace app
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

bool ModbusCodec::decode(ModbusTcpAdu& adu)
{
    adu.transactionId = buf.readBe();
    adu.protocolId = buf.readBe();
    adu.pktLen = buf.readBe();
    adu.slaveAddr = buf.read();
    adu.func = buf.read();

    return true;
}

} // namespace app
