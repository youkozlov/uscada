#pragma once

#include "ModbusInitRsp.hpp"
#include "ModbusReleaseRsp.hpp"
#include "ModbusConfigRsp.hpp"
#include "ModbusClientAduRsp.hpp"
#include "ModbusAduReq.hpp"

#include "Logger.hpp"

namespace app::controller
{

class ModbusTestFsm;

class ModbusTestState
{
public:
    virtual ~ModbusTestState() {}

    virtual char const* name() const = 0;

    virtual void onStart(ModbusTestFsm&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onModbusInitRspReceive(ModbusTestFsm&, ModbusInitRsp const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onModbusReleaseRspReceive(ModbusTestFsm&, ModbusReleaseRsp const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onModbusConfigRspReceive(ModbusTestFsm&, ModbusConfigRsp const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onModbusClientAduRspReceive(ModbusTestFsm&, ModbusClientAduRsp const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onModbusAduReqReceive(ModbusTestFsm&, ModbusAduReq const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onStop(ModbusTestFsm&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onTimer(ModbusTestFsm&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onEnter(ModbusTestFsm&) {}

    virtual void onExit(ModbusTestFsm&) {}
};

} // namespace app::controller
