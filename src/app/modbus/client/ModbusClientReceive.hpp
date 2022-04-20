#pragma once

#include "ModbusClientState.hpp"

namespace app
{

class ModbusClientReceive : public ModbusClientState
{
public:
    explicit ModbusClientReceive() {}

    void onEnter(ModbusClientFsm&) final;

    void onDataReceived(ModbusClientFsm&) final;

    void onError(ModbusClientFsm&) final;

    void onTimer(ModbusClientFsm&) final;

    void onExit(ModbusClientFsm&) final;

private:
    /* data */
};

} // namespace app