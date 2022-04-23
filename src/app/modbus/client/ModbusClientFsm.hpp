#pragma once

#include "Singleton.hpp"
#include "ModbusClientState.hpp"

namespace app::modbus
{

class ModbusClient;
class ModbusClientState;

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
        state->onExit(*this);
        state = &getSingleton<NEW_STATE>();
        state->onEnter(*this);
    }
};

} // namespace app::modbus
