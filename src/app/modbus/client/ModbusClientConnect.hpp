#pragma once

#include "ModbusClientState.hpp"

namespace app
{

class ModbusClientConnect : public ModbusClientState
{
public:
    explicit ModbusClientConnect() {}

    void onEnter(ModbusClientFsm&) final;

    void onConnected(ModbusClientFsm&) final;

    void onError(ModbusClientFsm&) final;

    void onTimer(ModbusClientFsm&) final;

    void onExit(ModbusClientFsm&) final;

private:
    /* data */
};

} // namespace app
