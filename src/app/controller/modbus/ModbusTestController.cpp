#include "ModbusTestController.hpp"

#include "ControllerSender.hpp"
#include "ControllerReactor.hpp"
#include "MsgModbusInitReq.hpp"
#include "MsgModbusInitRsp.hpp"
#include "MsgModbusReleaseReq.hpp"
#include "MsgModbusReleaseRsp.hpp"
#include "MsgModbusConfigReq.hpp"
#include "MsgModbusConfigRsp.hpp"
#include "MsgModbusClientAduReq.hpp"
#include "MsgModbusClientAduRsp.hpp"
#include "MsgModbusAduReq.hpp"
#include "MsgModbusAduRsp.hpp"

#include "Logger.hpp"

#include <chrono>
#include <thread>
#include <cstring>

namespace app::controller
{

namespace
{
std::vector<uint8_t> randVector(unsigned len)
{
    std::vector<uint8_t> vect(len);
    ::srand(0);
    for (auto& it : vect)
    {
        it = ::rand() % 65535;
    }
    return vect;
}
}

ModbusTestController::ModbusTestController()
    : fsm(*this)
    , timer(Reactor::get().createTimer([this](){ onTimerEvent(); }))
    , testCaseCounter(0)
{
    testCases =
    {
        {
            {0, 1, ModbusFunction::presetMultipleRegisters, 890, 120, randVector(120 * 2)},
            {ModbusError::noerror, MsgStatus::success, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::readInputRegisters, 0, 126, {}},
            {ModbusError::noerror, MsgStatus::error, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::readInputRegisters, 10, 10, {}},
            {ModbusError::serverDeviceFailure, MsgStatus::success, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::readInputRegisters, 890, 120, {}},
            {ModbusError::noerror, MsgStatus::success, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::presetSingleRegister, 190, 0, randVector(2)},
            {ModbusError::noerror, MsgStatus::success, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::presetSingleRegister, 190, 10, randVector(2)},
            {ModbusError::noerror, MsgStatus::error, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::presetSingleRegister, 190, 0, {}},
            {ModbusError::noerror, MsgStatus::error, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::presetMultipleRegisters, 890, 120, randVector(120 * 2)},
            {ModbusError::noerror, MsgStatus::success, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::presetMultipleRegisters, 256, 1, randVector(1 * 2)},
            {ModbusError::noerror, MsgStatus::success, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::presetMultipleRegisters, 256, 1, randVector(1 * 4)},
            {ModbusError::noerror, MsgStatus::error, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::readInputRegisters, 10, 125, {}},
            {ModbusError::noerror, MsgStatus::success, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::readInputRegisters, 0, 0, {}},
            {ModbusError::noerror, MsgStatus::success, randVector(2048)}
        },
        {
            {99, 1, ModbusFunction::readInputRegisters, 10, 125, {}},
            {ModbusError::noerror, MsgStatus::error, randVector(2048)}
        },
        {
            {0, 1, static_cast<ModbusFunction>(99), 10, 125, {}},
            {ModbusError::noerror, MsgStatus::error, randVector(2048)}
        },
        {
            {0, 248, ModbusFunction::readInputRegisters, 10, 125, {}},
            {ModbusError::noerror, MsgStatus::error, randVector(2048)}
        },
        {
            {0, 1, ModbusFunction::presetSingleRegister, 190, 0, randVector(2)},
            {ModbusError::noerror, MsgStatus::error, randVector(2048)}
        },
    };
}

void ModbusTestController::receive(MsgControllerStartReq const&)
{
    fsm.getState().onStart(fsm);
}

void ModbusTestController::receive(MsgControllerStopReq const&)
{
    fsm.getState().onStop(fsm);
}

void ModbusTestController::receive(MsgModbusInitRsp const& rsp)
{
    fsm.getState().onModbusInitRspReceive(fsm, rsp);
}

void ModbusTestController::receive(MsgModbusReleaseRsp const& rsp)
{
    fsm.getState().onModbusReleaseRspReceive(fsm, rsp);
}

void ModbusTestController::receive(MsgModbusConfigRsp const& rsp)
{
    fsm.getState().onModbusConfigRspReceive(fsm, rsp);
}

void ModbusTestController::receive(MsgModbusClientAduRsp const& rsp)
{
    fsm.getState().onModbusClientAduRspReceive(fsm, rsp);
}

void ModbusTestController::receive(MsgModbusAduReq const& req)
{
    fsm.getState().onModbusAduReqReceive(fsm, req);
}

void ModbusTestController::onTimerEvent()
{
    fsm.getState().onTimer(fsm);
}

void ModbusTestController::resetTestCaseCounter()
{
    testCaseCounter = 0;
}

void ModbusTestController::startTimer(long timeout)
{
    timer->start(timeout);
}

void ModbusTestController::stopTimer()
{
    timer->stop();
}

void ModbusTestController::sendModbusInitReq()
{
    reactor::MsgStore<MsgModbusInitReq> msgStore;
    MsgModbusInitReq& req = msgStore.getMsg();
    req.maxNumServers = 1;
    req.maxNumClients = 1;
    Sender::sendMsg(msgStore);
}

void ModbusTestController::sendModbusConfigReq()
{
    reactor::MsgStore<MsgModbusConfigReq> msgStore;
    MsgModbusConfigReq& req = msgStore.getMsg();
    EntityId id = 0;
    req.numItems = 0;
    for (unsigned i = 0; i < 1u; ++i)
    {
        ModbusConfig& item = req.items[req.numItems++];
        item.id = id++;
        item.mode = ModbusConfig::Mode::client;
        item.addr.data[0] = 0x7f;
        item.addr.data[1] = 0x0;
        item.addr.data[2] = 0x0;
        item.addr.data[3] = 0x1;
        item.addr.data[4] = 0x2f;
        item.addr.data[5] = 0x71;
    }
    id = 0;
    for (unsigned i = 0; i < 1u; ++i)
    {
        ModbusConfig& item = req.items[req.numItems++];
        item.id = id++;
        item.mode = ModbusConfig::Mode::server;
        item.addr.data[0] = 0x7f;
        item.addr.data[1] = 0x0;
        item.addr.data[2] = 0x0;
        item.addr.data[3] = 0x1;
        item.addr.data[4] = 0x2f;
        item.addr.data[5] = 0x71;
    }
    Sender::sendMsg(msgStore);
}

void ModbusTestController::sendModbusClientAduReq()
{
    reactor::MsgStore<MsgModbusClientAduReq> msgStore;
    MsgModbusClientAduReq& req = msgStore.getMsg();

    req.numItems = testCases.size();
    for (unsigned testCaseId = 0; testCaseId < req.numItems; ++testCaseId)
    {
        auto const& it = testCases[testCaseId];

        LM(CTRL, LD, "TEST CASE: %u, func-%s, startItem-%u, numItems-%u"
            , testCaseId, toString(it.req.func), it.req.startItem, it.req.numItems);

        auto& item = req.item(testCaseId);

        item.clientId = it.req.clientId;
        item.transactId = testCaseId;
        item.addr = it.req.addr;
        item.func = it.req.func;
        item.startItem = it.req.startItem;
        item.numItems = it.req.numItems;
        item.numBytes = it.req.data.size();
        if (it.req.data.size())
        {
            std::memcpy(&item.data[0], &it.req.data[0], it.req.data.size());
        }
    }

    Sender::sendMsg(msgStore);
}

Result ModbusTestController::process(MsgModbusClientAduRsp const& rsp)
{
    testCaseCounter += 1;

    auto const& it = testCases[rsp.transactId];

    if (it.req.clientId != rsp.clientId)
    {
        LM(CTRL, LE, "TEST CASE: %u, INVALID clientId", rsp.transactId);
        return Result::error;
    }

    if (it.rsp.status != rsp.status)
    {
        LM(CTRL, LE, "TEST CASE: %u, INVALID status", rsp.transactId);
        return Result::error;
    }

    if (it.rsp.error != rsp.error)
    {
        LM(CTRL, LE, "TEST CASE: %u, INVALID modbus error", rsp.transactId);
        return Result::error;
    }

    if (rsp.status != MsgStatus::error && rsp.error == ModbusError::noerror)
    {
        switch (it.req.func)
        {
        case ModbusFunction::readHoldingRegisters:
        case ModbusFunction::readInputRegisters:
        {
            if (it.req.numItems * 2 != rsp.numBytes)
            {
                LM(CTRL, LE, "TEST CASE: %u, INVALID numBytes", rsp.transactId);
                return Result::error;
            }
            if (std::memcmp(&rsp.data[0], &it.rsp.data[it.req.startItem * 2], it.req.numItems * 2))
            {
                LM(CTRL, LE, "TEST CASE: %u, INVALID data", rsp.transactId);
                return Result::error;
            }
        }
        break;
        case ModbusFunction::presetSingleRegister:
        {
            if (2 != rsp.numBytes)
            {
                LM(CTRL, LE, "TEST CASE: %u, INVALID numBytes", rsp.transactId);
                return Result::error;
            }
            if (std::memcmp(&it.req.data[0], &it.rsp.data[it.req.startItem * 2], it.req.data.size()))
            {
                LM(CTRL, LE, "TEST CASE: %u, INVALID data", rsp.transactId);
                return Result::error;
            }
        }
        break;
        case ModbusFunction::presetMultipleRegisters:
        {
            if (0 != rsp.numBytes)
            {
                LM(CTRL, LE, "TEST CASE: %u, INVALID numBytes", rsp.transactId);
                return Result::error;
            }
            if (std::memcmp(&it.req.data[0], &it.rsp.data[it.req.startItem * 2], it.req.data.size()))
            {
                LM(CTRL, LE, "TEST CASE: %u, INVALID data", rsp.transactId);
                return Result::error;
            }
        }
        break;
        default:
            LM(CTRL, LE, "TEST CASE: %u, Unexpected", rsp.transactId);
            return Result::error;
        break;
        }
    }
    return testCaseCounter == testCases.size() ? Result::done : Result::noerror;
}

void ModbusTestController::sendModbusReleaseReq()
{
    reactor::MsgStore<MsgModbusReleaseReq> msgStore;
    Sender::sendMsg(msgStore);
}

void ModbusTestController::process(MsgModbusInitRsp const&)
{
}

void ModbusTestController::process(MsgModbusReleaseRsp const&)
{
}

void ModbusTestController::process(MsgModbusConfigRsp const&)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
}

Result ModbusTestController::process(MsgModbusAduReq const& req)
{
    auto& it = testCases[req.transactId];

    switch (req.func)
    {
    case ModbusFunction::readHoldingRegisters:
    case ModbusFunction::readInputRegisters:
    {
        reactor::MsgStore<MsgModbusAduRsp> msgStore;
        MsgModbusAduRsp& rsp = msgStore.getMsg();
        rsp.serverId = req.serverId;
        rsp.sessionId = req.sessionId;
        rsp.transactId = req.transactId;
        rsp.error = it.rsp.error;
        rsp.status = it.rsp.status;
        rsp.numBytes = req.numItems * 2;
        std::memcpy(&rsp.data[0], &it.rsp.data[req.startItem * 2], rsp.numBytes);
        Sender::sendMsg(msgStore);
    }
    break;
    case ModbusFunction::presetSingleRegister:
    {
        reactor::MsgStore<MsgModbusAduRsp> msgStore;
        MsgModbusAduRsp& rsp = msgStore.getMsg();
        rsp.serverId = req.serverId;
        rsp.sessionId = req.sessionId;
        rsp.transactId = req.transactId;
        rsp.error = it.rsp.error;
        rsp.status = it.rsp.status;
        rsp.numBytes = req.numBytes;
        std::memcpy(&it.rsp.data[req.startItem * 2], &req.data[0], req.numBytes);
        std::memcpy(&rsp.data[0], &req.data[0], req.numBytes);
        Sender::sendMsg(msgStore);
    }
    break;
    case ModbusFunction::presetMultipleRegisters:
    {
        reactor::MsgStore<MsgModbusAduRsp> msgStore;
        MsgModbusAduRsp& rsp = msgStore.getMsg();
        rsp.serverId = req.serverId;
        rsp.sessionId = req.sessionId;
        rsp.transactId = req.transactId;
        rsp.error = it.rsp.error;
        rsp.status = it.rsp.status;
        rsp.numBytes = 0;
        std::memcpy(&it.rsp.data[req.startItem * 2], &req.data[0], req.numBytes);
        Sender::sendMsg(msgStore);
    }
    break;
    default:
    {
        reactor::MsgStore<MsgModbusAduRsp> msgStore;
        MsgModbusAduRsp& rsp = msgStore.getMsg();
        rsp.serverId = req.serverId;
        rsp.sessionId = req.sessionId;
        rsp.transactId = req.transactId;
        rsp.error = it.rsp.error;
        rsp.status = it.rsp.status;
        rsp.numBytes = 0;
        Sender::sendMsg(msgStore);
    }
    break;
    }
    return Result::done;
}

} // namespace app::controller
