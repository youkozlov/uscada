#pragma once

#include "Logger.hpp"

namespace app
{

class ModbusClientFsm;

class ModbusClientState
{
public:
    virtual ~ModbusClientState() {}

    virtual void start(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onConnected(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onDataReceived(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onError(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onTimer(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onEnter(ModbusClientFsm&) {}

    virtual void onExit(ModbusClientFsm&) {}
};

} // namespace app
