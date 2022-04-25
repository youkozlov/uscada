#pragma once

#include "ModbusClientState.hpp"

namespace app::modbus
{

class ModbusClientConnected : public ModbusClientState
{
public:
    explicit ModbusClientConnected() {}

    char const* name() const final { return "ModbusClientConnected"; }

    void onReceiveTransactionReq(ModbusClientFsm&) final;

    void onDataReceived(ModbusClientFsm&) final;

private:

};

} // namespace a::modbuspp