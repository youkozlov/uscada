#pragma once

#include "ModbusTestState.hpp"

namespace app::controller
{

class ModbusTestInit : public ModbusTestState
{
public:
    explicit ModbusTestInit() {}

    char const* name() const final { return "ModbusTestInit"; }

    void onEnter(ModbusTestFsm&) final;

    void onStart(ModbusTestFsm&) final;

    void onStop(ModbusTestFsm&) final;

    void onModbusInitRspReceive(ModbusTestFsm&, MsgModbusInitRsp const&) final;

    void onModbusReleaseRspReceive(ModbusTestFsm&, MsgModbusReleaseRsp const&) final;

private:
    /* data */
};

} // namespace app::controller
