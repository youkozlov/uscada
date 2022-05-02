#pragma once

#include <array>
#include <cstdint>

#include "ReactorInterface.hpp"
#include "TimerHandler.hpp"
#include "TimerPtr.hpp"
#include "ModbusTestFsm.hpp"

namespace app
{
struct ControllerStartReq;
struct ControllerStopReq;
struct ModbusInitRsp;
struct ModbusReleaseRsp;
struct ModbusConfigRsp;
struct ModbusClientAduRsp;
struct ModbusAduReq;
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

    void receive(ControllerStartReq const&);
    void receive(ControllerStopReq const&);
    void receive(ModbusInitRsp const&);
    void receive(ModbusReleaseRsp const&);
    void receive(ModbusConfigRsp const&);
    void receive(ModbusClientAduRsp const&);
    void receive(ModbusAduReq const&);

    void resetTestCaseCounter();
    void startTimer(long);
    void stopTimer();
    void sendModbusInitReq();
    void sendModbusConfigReq();
    void sendModbusReleaseReq();
    void process(ModbusInitRsp const&);
    void process(ModbusReleaseRsp const&);
    void process(ModbusConfigRsp const&);

    void sendModbusClientAduReq();
    Result process(ModbusClientAduRsp const&);
    Result process(ModbusAduReq const&);

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
