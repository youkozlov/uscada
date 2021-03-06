#pragma once

#include "ModbusClientState.hpp"

namespace app::modbus
{

class ModbusClientBackoff : public ModbusClientState
{
public:
    explicit ModbusClientBackoff() {}

    char const* name() const final { return "ModbusClientBackoff"; }

    void onEnter(ModbusClientFsm&) final;

    void onReceiveTransactionReq(ModbusClientFsm&) final;

    void onTimer(ModbusClientFsm&) final;

    void onExit(ModbusClientFsm&) final;

private:
    /* data */
};

} // namespace app::modbus
