#pragma once

#include "ModbusClientState.hpp"

namespace app::modbus
{

class ModbusClientConnect : public ModbusClientState
{
public:
    explicit ModbusClientConnect() {}

    char const* name() const final { return "ModbusClientConnect"; }

    void onEnter(ModbusClientFsm&) final;

    void onReceiveTransactionReq(ModbusClientFsm&) final;

    void onConnected(ModbusClientFsm&) final;

    void onError(ModbusClientFsm&) final;

    void onTimer(ModbusClientFsm&) final;

    void onExit(ModbusClientFsm&) final;

private:
    /* data */
};

} // namespace app::modbus
