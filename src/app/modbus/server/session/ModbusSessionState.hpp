#pragma once

#include "Logger.hpp"
#include "MsgModbusAduRsp.hpp"

namespace app::modbus
{

class ModbusSessionFsm;

class ModbusSessionState
{
public:
    virtual ~ModbusSessionState() {}

    virtual char const* name() const = 0;

    virtual void onStart(ModbusSessionFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onDataReceived(ModbusSessionFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onModbusAduRspReceive(ModbusSessionFsm&, MsgModbusAduRsp const&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onTimer(ModbusSessionFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onEnter(ModbusSessionFsm&) {}

    virtual void onExit(ModbusSessionFsm&) {}
};

} // namespace app::modbus
