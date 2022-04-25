#pragma once

#include "ModbusClientState.hpp"

namespace app::modbus
{

class ModbusClientSend : public ModbusClientState
{
public:
    explicit ModbusClientSend() {}

    char const* name() const final { return "ModbusClientSend"; }

    void onEnter(ModbusClientFsm&) final;

    void onReceiveTransactionReq(ModbusClientFsm&) final;

    void onDataReceived(ModbusClientFsm&) final;

    void onTimer(ModbusClientFsm&) final;

    void onExit(ModbusClientFsm&) final;

private:

    void send(ModbusClientFsm&);

};

} // namespace a::modbuspp