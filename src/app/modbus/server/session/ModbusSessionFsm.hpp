#pragma once

#include "Singleton.hpp"
#include "ModbusSessionState.hpp"
#include "Logger.hpp"

namespace app::modbus
{

class ModbusSession;

class ModbusSessionFsm
{
public:

    explicit ModbusSessionFsm(ModbusSession&);

    ~ModbusSessionFsm();

    ModbusSessionState& getState();

    ModbusSession& getEntity();

private:
    ModbusSessionState* state;
    ModbusSession& entity;

public:
    template <typename NEW_STATE>
    void transit()
    {
        auto* newState = &getSingleton<NEW_STATE>();
        if (newState == state)
        {
            LM(MODBUS, LE, "Invalid transition");
            return;
        }
        LM(MODBUS, LD, "Transit: %s -> %s", state->name(), newState->name());
        state->onExit(*this);
        state = &getSingleton<NEW_STATE>();
        state->onEnter(*this);
    }
};

} // namespace app::modbus
