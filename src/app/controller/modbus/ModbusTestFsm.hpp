#pragma once

#include "Singleton.hpp"
#include "ModbusTestState.hpp"
#include "Logger.hpp"

namespace app::controller
{

class ModbusTestController;

class ModbusTestFsm
{
public:

    explicit ModbusTestFsm(ModbusTestController&);

    ~ModbusTestFsm();

    ModbusTestState& getState();

    ModbusTestController& getEntity();

private:
    ModbusTestState* state;
    ModbusTestController& entity;

public:
    template <typename NEW_STATE>
    void transit()
    {
        auto* newState = &getSingleton<NEW_STATE>();
        if (newState == state)
        {
            LM(CTRL, LE, "Invalid transition");
            return;
        }
        LM(CTRL, LD, "Transit: %s -> %s", state->name(), newState->name());
        state->onExit(*this);
        state = &getSingleton<NEW_STATE>();
        state->onEnter(*this);
    }
};

} // namespace app::controller
