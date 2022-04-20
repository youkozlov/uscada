#pragma once

#include "ModbusClientState.hpp"

namespace app
{

class ModbusClientInit : public ModbusClientState
{
public:
    explicit ModbusClientInit() {}

    void start(ModbusClientFsm&) final;

private:
    /* data */
};

} // namespace app
