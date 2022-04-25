#include "ModbusCodec.hpp"
#include "Logger.hpp"
#include "MsgUtils.hpp"

namespace app::modbus
{

ModbusCodec::ModbusCodec(PduBuffer& buf_)
    : buf(buf_)
{
}

unsigned ModbusCodec::aduPktLen() const
{
    unsigned hh = buf.begin()[aduLenOffset + 0];
    unsigned ll = buf.begin()[aduLenOffset + 1];
    return (hh << 8) | ll;
}

unsigned ModbusCodec::pduLen(ModbusFunction func, unsigned numItems) const
{
    switch (func)
    {
    case ModbusFunction::readCoilStatus:
    case ModbusFunction::readDiscreteInputs:
    case ModbusFunction::forceSingleCoil:
    case ModbusFunction::presetSingleRegister:
    {
        return pduFuncCodeLen + numBytesLen + (numItems + 7) / 8;
    }
    break;
    case ModbusFunction::readHoldingRegisters:
    case ModbusFunction::readInputRegisters:
    case ModbusFunction::presetMultipleRegisters:
    {
        return pduFuncCodeLen + numBytesLen + numItems * 2;
    }
    break;
    default:
    {
        LM(MODBUS, LE, "ADU encode, unsupported function (%s)", toString(func));
        return false;
    }
    }
}

bool ModbusCodec::isAduHdrReceived() const
{
    return buf.size() >= aduHdrLen;
}

bool ModbusCodec::isAduReceived() const
{
    return buf.size() >= aduPktLen();
}

bool ModbusCodec::isAduDataLenValid() const
{
    return (aduPktLen() + aduHdrLen) < maxAduLen;
}

bool ModbusCodec::isAduValid() const
{
    return buf.size() < maxAduLen && (aduPktLen() + aduHdrLen) == buf.size();
}

bool ModbusCodec::encode(AduRequest const& adu)
{
    if (std::min(adu.addr, maxAddr) != adu.addr || std::max(adu.addr, minAddr) != adu.addr)
    {
        LM(MODBUS, LE, "ADU encode, unexpected slave address(%u)", adu.addr);
        return false;
    }
    switch (adu.func)
    {
    case ModbusFunction::readCoilStatus:
    case ModbusFunction::readDiscreteInputs:
    case ModbusFunction::readHoldingRegisters:
    case ModbusFunction::readInputRegisters:
    {
        if (pduLen(adu.func, adu.numItems) > maxPduLen)
        {
            LM(MODBUS, LE, "ADU encode, unexpected number of items(%u) in request", adu.numItems);
            return false;
        }
        buf.writeBe(adu.transactId);
        buf.writeBe(modbusProtocolId);
        buf.writeBe(1 + 1 + 2 + 2);
        buf.write(adu.addr);
        buf.write(toUint8(adu.func));
        buf.writeBe(adu.startItem);
        buf.writeBe(adu.numItems);
    }
    break;
    case ModbusFunction::forceSingleCoil:
    case ModbusFunction::presetSingleRegister:
    {
        if (adu.numItems != 0)
        {
            LM(MODBUS, LW, "ADU encode, unexpected number items");
            return false;
        }
        if (adu.numBytes != 2)
        {
            LM(MODBUS, LW, "ADU encode, unexpected number of bytes");
            return false;
        }
        if (adu.func == ModbusFunction::forceSingleCoil)
        {
            if ((adu.data[1] != 0x0) || (adu.data[0] != 0x0 && adu.data[0] != 0xFF))
            {
                unsigned hh = adu.data[0];
                unsigned ll = adu.data[1];
                LM(MODBUS, LW, "ADU encode, expected value is 0xFF00 | 0x0000, but given %u", (hh << 8) | ll);
                return false;
            }
        }
        buf.writeBe(adu.transactId);
        buf.writeBe(modbusProtocolId);
        buf.writeBe(1 + 1 + 2 + 2);
        buf.write(adu.addr);
        buf.write(toUint8(adu.func));
        buf.writeBe(adu.startItem);
        buf.write(adu.data[1]);
        buf.write(adu.data[0]);
    }
    break;
    case ModbusFunction::presetMultipleRegisters:
    {
        if (adu.numBytes != adu.numItems * 2)
        {
            LM(MODBUS, LE, "ADU encode, unexpected number of bytes");
            return false;
        }
        buf.writeBe(adu.transactId);
        buf.writeBe(modbusProtocolId);
        buf.writeBe(1 + 1 + 2 + 2 + 1 + adu.numBytes);
        buf.write(adu.addr);
        buf.write(toUint8(adu.func));
        buf.writeBe(adu.startItem);
        buf.writeBe(adu.numItems);
        buf.write(adu.numBytes);
        for (unsigned i = 0; i < adu.numBytes; i += 2)
        {
            buf.write(adu.data[i + 1]);
            buf.write(adu.data[i + 0]);
        }
    }
    break;
    default:
    {
        LM(MODBUS, LE, "ADU encode, unsupported function (%s)", toString(adu.func));
        return false;
    }
    }
    if (buf.size() > maxAduLen)
    {
        LM(MODBUS, LE, "ADU encode, unexpected size of ADU(%u)", buf.size());
        return false;
    }
    return true;
}

bool ModbusCodec::decode(AduRequest& adu)
{
    adu.transactId = buf.readBe();
    if (modbusProtocolId != buf.readBe())
    {
        LM(MODBUS, LW, "ADU decode, unexpected protocol id");
        return false;
    }
    uint16_t const pktLen = buf.readBe();
    adu.addr = buf.read();
    if (std::min(adu.addr, maxAddr) != adu.addr || std::max(adu.addr, minAddr) != adu.addr)
    {
        LM(MODBUS, LE, "ADU decode, unexpected slave address(%u)", adu.addr);
        return false;
    }
    adu.func = fromUint8<ModbusFunction>(buf.read());
    switch (adu.func)
    {
    case ModbusFunction::readCoilStatus:
    case ModbusFunction::readDiscreteInputs:
    case ModbusFunction::readHoldingRegisters:
    case ModbusFunction::readInputRegisters:
    {
        if (pktLen != 6)
        {
            LM(MODBUS, LW, "ADU decode, unexpected length of packet %u", pktLen);
            return false;
        }
        adu.startItem = buf.readBe();
        adu.numItems = buf.readBe();
        if (pduLen(adu.func, adu.numItems) > maxPduLen)
        {
            LM(MODBUS, LE, "ADU decode, unexpected number of items(%u) in request", adu.numItems);
            return false;
        }
    }
    break;
    case ModbusFunction::forceSingleCoil:
    case ModbusFunction::presetSingleRegister:
    {
        if (pktLen != 6)
        {
            LM(MODBUS, LW, "ADU decode, unexpected length of packet %u", pktLen);
            return false;
        }
        adu.startItem = buf.readBe();
        adu.numBytes = 2;
        adu.data[1] = buf.read();
        adu.data[0] = buf.read();
    }
    break;
    case ModbusFunction::presetMultipleRegisters:
    {
        adu.startItem = buf.readBe();
        adu.numItems = buf.readBe();
        adu.numBytes = buf.read();
        if (adu.numBytes != adu.numItems * 2)
        {
            LM(MODBUS, LW, "ADU encode, unexpected number of bytes");
            return false;
        }
        if (pktLen != 7 + adu.numBytes)
        {
            LM(MODBUS, LW, "ADU decode, unexpected length of packet %u", pktLen);
            return false;
        }
        for (unsigned i = 0; i < adu.numBytes; i += 2)
        {
            adu.data[i + 1] = buf.read();
            adu.data[i + 0] = buf.read();
        }
    }
    break;
    default:
    {
        LM(MODBUS, LE, "ADU decode, unsupported function (%s)", toString(adu.func));
        return false;
    }
    break;
    }
    return true;
}

bool ModbusCodec::encode(AduRespond const& adu)
{
    switch (adu.func)
    {
    case ModbusFunction::modbusError:
    {
        buf.writeBe(adu.transactId);
        buf.writeBe(modbusProtocolId);
        buf.writeBe(1 + 1 + 1);
        buf.write(adu.addr);
        buf.write(toUint8(adu.func));
        buf.write(toUint8(adu.error));
    }
    break;
    case ModbusFunction::readHoldingRegisters:
    case ModbusFunction::readInputRegisters:
    {
        buf.writeBe(adu.transactId);
        buf.writeBe(modbusProtocolId);
        buf.writeBe(1 + 1 + 1 + adu.numBytes);
        buf.write(adu.addr);
        buf.write(toUint8(adu.func));
        buf.write(adu.numBytes);
        if (adu.numBytes % 2)
        {
            LM(MODBUS, LW, "ADU encode, unexpected number of bytes: %u", adu.numBytes);
            return false;
        }
        for (unsigned i = 0; i < adu.numBytes; i += 2)
        {
            buf.write(adu.data[i + 1]);
            buf.write(adu.data[i + 0]);
        }
    }
    break;
    case ModbusFunction::forceSingleCoil:
    case ModbusFunction::presetSingleRegister:
    {
        if (adu.numBytes != 2)
        {
            LM(MODBUS, LW, "ADU encode, unexpected number of bytes");
            return false;
        }
        if (adu.func == ModbusFunction::forceSingleCoil)
        {
            if ((adu.data[1] != 0x0) || (adu.data[0] != 0x0 && adu.data[0] != 0xFF))
            {
                unsigned hh = adu.data[0];
                unsigned ll = adu.data[1];
                LM(MODBUS, LW, "ADU encode, expected value is 0xFF00 | 0x0000, but given %u", (hh << 8) | ll);
                return false;
            }
        }
        buf.writeBe(adu.transactId);
        buf.writeBe(modbusProtocolId);
        buf.writeBe(1 + 1 + 2 + 2);
        buf.write(adu.addr);
        buf.write(toUint8(adu.func));
        buf.writeBe(adu.startItem);
        buf.write(adu.data[1]);
        buf.write(adu.data[0]);
    }
    break;
    case ModbusFunction::presetMultipleRegisters:
    {
        buf.writeBe(adu.transactId);
        buf.writeBe(modbusProtocolId);
        buf.writeBe(1 + 1 + 2 + 2);
        buf.write(adu.addr);
        buf.write(toUint8(adu.func));
        buf.writeBe(adu.startItem);
        buf.writeBe(adu.numItems);
    }
    break;
    default:
    {
        LM(MODBUS, LE, "ADU encode, unsupported function (%s)", toString(adu.func));
        return false;
    }
    break;
    }
    if (buf.size() > maxAduLen)
    {
        LM(MODBUS, LE, "ADU encode, unexpected size of ADU(%u)", buf.size());
        return false;
    }
    return true;
}

bool ModbusCodec::decode(AduRespond& adu)
{
    adu.transactId = buf.readBe();
    if (modbusProtocolId != buf.readBe())
    {
        LM(MODBUS, LW, "ADU decode, unexpected protocol id");
        return false;
    }
    uint16_t const pktLen = buf.readBe();
    adu.addr = buf.read();
    adu.func = fromUint8<ModbusFunction>(buf.read());

    switch (adu.func)
    {
    case ModbusFunction::modbusError:
    {
        adu.error = fromUint8<ModbusError>(buf.read());
    }
    break;
    case ModbusFunction::readHoldingRegisters:
    case ModbusFunction::readInputRegisters:
    {
        adu.numBytes = buf.read();
        if (pktLen != adu.numBytes + 3)
        {
            LM(MODBUS, LW, "ADU decode, unexpected number of bytes: %u", adu.numBytes);
            return false;
        }
        if (adu.numBytes % 2)
        {
            LM(MODBUS, LW, "ADU decode, unexpected number of bytes: %u", adu.numBytes);
            return false;
        }
        for (unsigned i = 0; i < adu.numBytes; i += 2)
        {
            adu.data[i + 1] = buf.read();
            adu.data[i + 0] = buf.read();
        }
    }
    break;
    case ModbusFunction::forceSingleCoil:
    case ModbusFunction::presetSingleRegister:
    {
        if (pktLen != 6)
        {
            LM(MODBUS, LW, "ADU decode, unexpected length of packet %u", pktLen);
            return false;
        }
        adu.startItem = buf.readBe();
        adu.numBytes = 2;
        adu.data[1] = buf.read();
        adu.data[0] = buf.read();
    }
    break;
    case ModbusFunction::presetMultipleRegisters:
    {
        if (pktLen != 6)
        {
            LM(MODBUS, LW, "ADU decode, unexpected length of packet %u", pktLen);
            return false;
        }
        adu.startItem = buf.readBe();
        adu.numItems = buf.readBe();
    }
    break;
    default:
    {
        LM(MODBUS, LE, "ADU decode, unsupported function (%s)", toString(adu.func));
        return false;
    }
    break;
    }
    return true;
}

} // namespace app::modbus
