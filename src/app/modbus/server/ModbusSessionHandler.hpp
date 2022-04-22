#pragma once

namespace app::modbus
{

class ModbusSession;

class ModbusSessionHandler
{
public:
    virtual ~ModbusSessionHandler() {}

    virtual void onRemoveSession(ModbusSession&) = 0;

    virtual void onAduReceived(ModbusSession&) = 0;
};

} // namespace app::modbus
