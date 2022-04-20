#pragma once

#include "ModbusClientState.hpp"

namespace app
{

class ModbusClientBackoff : public ModbusClientState
{
public:
    explicit ModbusClientBackoff() {}

    void onEnter(ModbusClientFsm&) final;

    void onTimer(ModbusClientFsm&) final;

    void onExit(ModbusClientFsm&) final;

private:
    /* data */
};

} // namespace app
