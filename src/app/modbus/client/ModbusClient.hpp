#pragma once

#include "SenderInterface.hpp"
#include "ReactorInterface.hpp"
#include "ModbusClientFsm.hpp"
#include "LinkHandler.hpp"
#include "LinkPtr.hpp"
#include "TimerPtr.hpp"

namespace app
{

class ModbusClient : public reactor::LinkHandler
{
public:
    explicit ModbusClient(reactor::SenderInterface&, reactor::ReactorInterface&);

    ~ModbusClient();

    void start();

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

    void onTimer();

    ModbusClientFsm fsm;
    reactor::LinkPtr link;
    reactor::TimerPtr timer;
};

} // namespace app
