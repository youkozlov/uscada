#pragma once

#include "ModbusSession.hpp"

namespace app::modbus
{

class ModbusSessionHandler
{
public:
    virtual ~ModbusSessionHandler() {}

    virtual void onReleaseSession(ModbusSession::Uid) = 0;
};

} // namespace app::modbus
