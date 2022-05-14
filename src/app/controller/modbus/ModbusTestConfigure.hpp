#pragma once

#include "ModbusTestState.hpp"

namespace app::controller
{

class ModbusTestConfigure : public ModbusTestState
{
public:
    explicit ModbusTestConfigure() {}

    char const* name() const final { return "ModbusTestConfigure"; }

    void onEnter(ModbusTestFsm&) final;

    void onModbusConfigRspReceive(ModbusTestFsm&, MsgModbusConfigRsp const&) final;

private:
    /* data */
};

} // namespace app::controller
