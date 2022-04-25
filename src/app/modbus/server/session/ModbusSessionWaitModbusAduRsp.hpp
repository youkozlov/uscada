#pragma once

#include "ModbusSessionState.hpp"

namespace app::modbus
{

class ModbusSessionWaitModbusAduRsp : public ModbusSessionState
{
public:
    explicit ModbusSessionWaitModbusAduRsp() {}

    char const* name() const final { return "ModbusSessionWaitModbusAduRsp"; }

    void onEnter(ModbusSessionFsm&) final;

    void onDataReceived(ModbusSessionFsm&) final;

    void onModbusAduRspReceive(ModbusSessionFsm&, ModbusAduRsp const&) final;

    void onTimer(ModbusSessionFsm&) final;

    void onExit(ModbusSessionFsm&) final;

private:
    /* data */
};

} // namespace app::modbus
