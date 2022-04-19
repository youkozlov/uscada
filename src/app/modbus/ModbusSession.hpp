#pragma once

#include "LinkHandler.hpp"
#include "LinkInterface.hpp"
#include "TimerInterface.hpp"
#include "SenderInterface.hpp"
#include "ReactorInterface.hpp"

namespace app
{

class ModbusSession : public reactor::LinkHandler
{
public:
    explicit ModbusSession(reactor::SenderInterface&, reactor::ReactorInterface&);

    ~ModbusSession();

    void connect();

private:
    static constexpr long connectTimeout = 500000;
    static constexpr long idleTimeout = 2000000;
    static constexpr long transactTimeout = 500000;
    static constexpr long backoffTimeout = 5000000;

    void onDataReceived() final;
    void onConnected() final;
    void onError() final;
    void onConnectTimer();
    void onIdleTimer();
    void onTransactTimer();
    void onBackoffTimer();

    reactor::LinkInterface& link;
    reactor::TimerInterface& connectTimer;
    reactor::TimerInterface& idleTimer;
    reactor::TimerInterface& transactTimer;
    reactor::TimerInterface& backoffTimer;
};

} // namespace app
