#pragma once

#include "MsgModbusInitRsp.hpp"
#include "MsgModbusReleaseRsp.hpp"
#include "MsgModbusConfigRsp.hpp"
#include "MsgModbusClientAduRsp.hpp"
#include "MsgModbusAduReq.hpp"

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

    virtual void onModbusInitRspReceive(ModbusTestFsm&, MsgModbusInitRsp const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onModbusReleaseRspReceive(ModbusTestFsm&, MsgModbusReleaseRsp const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onModbusConfigRspReceive(ModbusTestFsm&, MsgModbusConfigRsp const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onModbusClientAduRspReceive(ModbusTestFsm&, MsgModbusClientAduRsp const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onModbusAduReqReceive(ModbusTestFsm&, MsgModbusAduReq const&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onStop(ModbusTestFsm&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onTimer(ModbusTestFsm&) { LM(CTRL, LE, "Unexpected call"); }

    virtual void onEnter(ModbusTestFsm&) {}

    virtual void onExit(ModbusTestFsm&) {}
};

} // namespace app::controller
