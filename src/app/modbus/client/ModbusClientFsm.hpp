#pragma once

#include "Singleton.hpp"
#include "ModbusClientState.hpp"

namespace app
{

class ModbusClient;
class ModbusClientState;

class ModbusClientFsm
{
public:

    explicit ModbusClientFsm(ModbusClient&);

    ~ModbusClientFsm();

    ModbusClientState& getState();

    void startTimer();

    void stopTimer();

    void connect();

    int send();

    int receive();

    void close();

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

} // namespace app
