#pragma once

#include "ModbusSessionState.hpp"

namespace app::modbus
{

class ModbusSessionConnected : public ModbusSessionState
{
public:
    explicit ModbusSessionConnected() {}

    char const* name() const final { return "ModbusSessionConnected"; }

    void onEnter(ModbusSessionFsm&) final;

    void onDataReceived(ModbusSessionFsm&) final;

    void onTimer(ModbusSessionFsm&) final;

    void onExit(ModbusSessionFsm&) final;

private:
};

} // namespace a::modbuspp