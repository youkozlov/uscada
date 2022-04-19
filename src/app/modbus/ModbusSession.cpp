#include "ModbusSession.hpp"

#include <iostream>

namespace app
{

ModbusSession::ModbusSession(reactor::SenderInterface&, reactor::ReactorInterface& reactor)
    : link(*reactor.createLink(*this))
    , connectTimer(*reactor.createTimer([this](){ onConnectTimer(); }))
    , idleTimer(*reactor.createTimer([this](){ onIdleTimer(); }))
    , transactTimer(*reactor.createTimer([this](){ onTransactTimer(); }))
    , backoffTimer(*reactor.createTimer([this](){ onBackoffTimer(); }))
{
}

ModbusSession::~ModbusSession()
{
}

void ModbusSession::onDataReceived()
{
    std::cout << "onDataReceived" << std::endl;

    transactTimer.stop();
    idleTimer.start(idleTimeout);
}

void ModbusSession::onConnected()
{
    std::cout << "onConnected" << std::endl;

    connectTimer.stop();
    idleTimer.start(idleTimeout);
}

void ModbusSession::onError()
{
    std::cout << "onError" << std::endl;

    connectTimer.stop();
    backoffTimer.start(backoffTimeout);
}

void ModbusSession::onConnectTimer()
{
    std::cout << "onConnectTimer" << std::endl;

    connectTimer.stop();
    backoffTimer.start(backoffTimeout);
    link.close();
}

void ModbusSession::onIdleTimer()
{
    std::cout << "onIdleTimer" << std::endl;

    idleTimer.stop();
    link.send("AAA\n", 5);
    transactTimer.start(transactTimeout);
}

void ModbusSession::onTransactTimer()
{
    std::cout << "onTransactTimer" << std::endl;

    transactTimer.stop();
    idleTimer.start(idleTimeout);
}

void ModbusSession::onBackoffTimer()
{
    std::cout << "onBackoffTimer" << std::endl;

    backoffTimer.stop();
    connect();
}

void ModbusSession::connect()
{
    reactor::LinkAddr addr;
    link.connect(addr);

    connectTimer.start(connectTimeout);
}

} // namespace app
