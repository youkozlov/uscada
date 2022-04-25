#pragma once

#include "ModbusAduRsp.hpp"
#include "Logger.hpp"

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

    virtual void onModbusAduRspReceive(ModbusSessionFsm&, ModbusAduRsp const&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onTimer(ModbusSessionFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onEnter(ModbusSessionFsm&) {}

    virtual void onExit(ModbusSessionFsm&) {}
};

} // namespace app::modbus
