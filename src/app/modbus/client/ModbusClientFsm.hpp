#pragma once

#include "Singleton.hpp"
#include "ModbusClientState.hpp"
#include "Logger.hpp"

namespace app::modbus
{

class ModbusClient;

class ModbusClientFsm
{
public:

    explicit ModbusClientFsm(ModbusClient&);

    ~ModbusClientFsm();

    ModbusClientState& getState();

    ModbusClient& getEntity();

private:
    ModbusClientState* state;
    ModbusClient& entity;

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
