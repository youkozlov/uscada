#pragma once

#include "ModbusClientState.hpp"

namespace app::modbus
{

class ModbusClientConnected : public ModbusClientState
{
public:
    explicit ModbusClientConnected() {}

    void onEnter(ModbusClientFsm&) final;

    void onReceiveTransactionReq(ModbusClientFsm&) final;

    void onDataReceived(ModbusClientFsm&) final;

    void onError(ModbusClientFsm&) final;

    void onTimer(ModbusClientFsm&) final;

    void onExit(ModbusClientFsm&) final;

private:

    void send(ModbusClientFsm&);

};

} // namespace a::modbuspp