#pragma once

#include <array>
#include <cstdint>

#include "ReactorInterface.hpp"
#include "TimerHandler.hpp"
#include "TimerPtr.hpp"
#include "ModbusTestFsm.hpp"

namespace app
{
struct MsgControllerStartReq;
struct MsgControllerStopReq;
struct MsgModbusInitRsp;
struct MsgModbusReleaseRsp;
struct MsgModbusConfigRsp;
struct MsgModbusClientAduRsp;
struct MsgModbusAduReq;
}

namespace app::controller
{

enum class Result
{
      noerror
    , done
    , error
};

class ModbusTestController
{
public:
    explicit ModbusTestController();

    void receive(MsgControllerStartReq const&);
    void receive(MsgControllerStopReq const&);
    void receive(MsgModbusInitRsp const&);
    void receive(MsgModbusReleaseRsp const&);
    void receive(MsgModbusConfigRsp const&);
    void receive(MsgModbusClientAduRsp const&);
    void receive(MsgModbusAduReq const&);

    void resetTestCaseCounter();
    void startTimer(long);
    void stopTimer();
    void sendModbusInitReq();
    void sendModbusConfigReq();
    void sendModbusReleaseReq();
    void process(MsgModbusInitRsp const&);
    void process(MsgModbusReleaseRsp const&);
    void process(MsgModbusConfigRsp const&);

    void sendModbusClientAduReq();
    Result process(MsgModbusClientAduRsp const&);
    Result process(MsgModbusAduReq const&);

    static constexpr long runDelay = 10000;

private:

    void onTimerEvent();

    ModbusTestFsm fsm;
    reactor::TimerPtr timer;
    struct Request
    {
        uint16_t clientId;
        uint16_t addr;
        ModbusFunction func;
        uint16_t startItem;
        uint16_t numItems;
        std::vector<uint8_t> data;
    };
    struct Respond
    {
        ModbusError           error;
        MsgStatus             status;
        std::vector<uint8_t>  data;
    };
    struct TestCase
    {
        Request req;
        Respond rsp;
    };
    std::vector<TestCase> testCases;
    unsigned testCaseCounter;
};

} // namespace app::controller
