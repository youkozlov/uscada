#pragma once

#include "SenderInterface.hpp"
#include "ReactorInterface.hpp"
#include "ModbusClientFsm.hpp"
#include "LinkHandler.hpp"
#include "TimerHandler.hpp"
#include "LinkInterface.hpp"
#include "TimerPtr.hpp"

namespace app
{
struct ModbusClientAduReq;
}

namespace app::modbus
{

class ModbusClient : public reactor::LinkHandler, public reactor::TimerHandler
{
public:
    explicit ModbusClient(reactor::ReactorInterface&);

    ~ModbusClient();

    void start();

    void receive(ModbusClientAduReq const&);

    void connect();

    void close();

    void startTimer();

    void stopTimer();

    int send();

    int receive();

private:
    static constexpr long timeout = 1000000;

    void onConnected() final;

    void onDataReceived() final;

    void onError() final;

    void onTimer() final;

    reactor::ReactorInterface& reactor;
    ModbusClientFsm fsm;
    reactor::LinkPtr link;
    reactor::TimerPtr timer;
};

} // namespace app::modbus
