#pragma once

#include "ModbusTestState.hpp"

namespace app::controller
{

class ModbusTestSetup : public ModbusTestState
{
public:
    explicit ModbusTestSetup() {}

    char const* name() const final { return "ModbusTestSetup"; }

    void onEnter(ModbusTestFsm&) final;

    void onTimer(ModbusTestFsm&) final;

    void onStop(ModbusTestFsm&) final;

    void onExit(ModbusTestFsm&) final;

private:
    /* data */
};

} // namespace app::controller
