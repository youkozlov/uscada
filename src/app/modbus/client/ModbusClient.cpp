#include "ModbusClient.hpp"
#include "LinkInterface.hpp"
#include "TimerInterface.hpp"
#include "ModbusCodec.hpp"
#include "PduBuffer.hpp"

namespace app
{

ModbusClient::ModbusClient(reactor::SenderInterface&, reactor::ReactorInterface& reactor)
    : fsm(*this)
    , link(reactor.createLink(*this))
    , timer(reactor.createTimer([this](){ onTimer(); }))
{
}

ModbusClient::~ModbusClient()
{
    timer->stop();
    link->close();
}

void ModbusClient::start()
{
    fsm.getState().start(fsm);
}

void ModbusClient::connect()
{
    reactor::LinkAddr addr;
    link->connect(addr);
}

void ModbusClient::close()
{
    link->close();
}

void ModbusClient::startTimer()
{
    timer->start(timeout);
}

void ModbusClient::stopTimer()
{
    timer->stop();
}

int ModbusClient::send()
{
    PduBuffer buf;
    ModbusCodec codec(buf);

    ModbusTcpAdu adu{};
    adu.startReg = 1;
    adu.numRegs = 2;
    adu.slaveAddr = 0x1;
    adu.func = 0x4;

    codec.encode(adu);

    int rc = link->send(buf.begin(), buf.size());
    if (rc <= 0)
    {
        return 0;
    }
    return 1;
}

int ModbusClient::receive()
{
    constexpr std::size_t aduHdrLen = 8;
    unsigned char rawBuf[256];
    int rc = link->receive(&rawBuf[0], aduHdrLen);
    if (rc <= 0)
    {
        return 0;
    }
    return 1;
}

void ModbusClient::onConnected()
{
    fsm.getState().onConnected(fsm);
}

void ModbusClient::onDataReceived()
{
    fsm.getState().onDataReceived(fsm);
}

void ModbusClient::onError()
{
    fsm.getState().onError(fsm);
}

void ModbusClient::onTimer()
{
    fsm.getState().onTimer(fsm);
}

} // namespace app
