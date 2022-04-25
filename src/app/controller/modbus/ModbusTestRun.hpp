#pragma once

#include "ModbusTestState.hpp"

namespace app::controller
{

class ModbusTestRun : public ModbusTestState
{
public:
    explicit ModbusTestRun() {}

    char const* name() const final { return "ModbusTestRun"; }

    void onEnter(ModbusTestFsm&) final;

    void onModbusClientAduRspReceive(ModbusTestFsm&, ModbusClientAduRsp const&) final;

    void onModbusAduReqReceive(ModbusTestFsm&, ModbusAduReq const&) final;

    void onStop(ModbusTestFsm&) final;

    void onExit(ModbusTestFsm&) final;

private:
    /* data */
};

} // namespace app::controller
