#pragma once

#include "ModbusClientState.hpp"

namespace app::modbus
{

class ModbusClientInit : public ModbusClientState
{
public:
    explicit ModbusClientInit() {}

    char const* name() const final { return "ModbusClientInit"; }

    void onStart(ModbusClientFsm&) final;

    void onReceiveTransactionReq(ModbusClientFsm&) final;

private:
    /* data */
};

} // namespace app::modbus
