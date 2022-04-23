#pragma once

#include "Logger.hpp"
#include "ModbusTransaction.hpp"

namespace app::modbus
{

class ModbusClientFsm;

class ModbusClientState
{
public:
    virtual ~ModbusClientState() {}

    virtual void onStart(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onConnected(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onReceiveTransactionReq(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onDataReceived(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onError(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onTimer(ModbusClientFsm&) { LM(MODBUS, LE, "Unexpected call"); }

    virtual void onEnter(ModbusClientFsm&) {}

    virtual void onExit(ModbusClientFsm&) {}
};

} // namespace app::modbus
