#pragma once

#include "ModbusSessionState.hpp"

namespace app::modbus
{

class ModbusSessionInit : public ModbusSessionState
{
public:
    explicit ModbusSessionInit() {}

    char const* name() const final { return "ModbusSessionInit"; }

    void onEnter(ModbusSessionFsm&) final;

    void onStart(ModbusSessionFsm&) final;

private:
    /* data */
};

} // namespace app::modbus
