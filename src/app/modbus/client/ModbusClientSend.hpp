#pragma once

#include "ModbusClientState.hpp"

namespace app
{

class ModbusClientSend : public ModbusClientState
{
public:
    explicit ModbusClientSend() {}

    void onEnter(ModbusClientFsm&) final;

    void onDataReceived(ModbusClientFsm&) final;

    void onTimer(ModbusClientFsm&) final;

    void onExit(ModbusClientFsm&) final;

private:
    /* data */
};

} // namespace app