#include "ModbusClient.hpp"
#include "LinkInterface.hpp"
#include "TimerInterface.hpp"
#include "ModbusCodec.hpp"
#include "PduBuffer.hpp"
#include "ModbusSender.hpp"
#include "ModbusClientAduReq.hpp"

#include "Logger.hpp"

namespace app::modbus
{

ModbusClient::ModbusClient(Init const& init)
    : uid(init.id)
    , reactor(init.reactor)
    , fsm(*this)
    , link(reactor.createLink(this))
    , timer(reactor.createTimer(this))
    , transactCounter(0)
{
    pduBuf.reset();
}

ModbusClient::~ModbusClient()
{
    LM(MODBUS, LD, "~ModbusClient");
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

void ModbusClient::startTimer(long timeout)
{
    timer->start(timeout);
}

void ModbusClient::stopTimer()
{
    timer->stop();
}

Status ModbusClient::send()
{
    if (trStorage.empty())
    {
        return Status::noerror;
    }

    ModbusTransaction const& tr = trStorage.front();

    ModbusTcpAdu adu{};
    adu.transactionId = tr.transactId;
    adu.startReg = tr.startReg;
    adu.numRegs = tr.numRegs;
    adu.slaveAddr = tr.addr;
    adu.func = tr.func;

    PduBuffer buf;
    ModbusCodec codec(buf);

    codec.encode(adu);

    LM(MODBUS, LD, "Client-%u, TX PDU %s", uid, buf.toString().c_str());

    int rc = link->send(buf.begin(), buf.size());
    if (rc <= 0)
    {
        return Status::error;
    }
    return Status::done;
}

void ModbusClient::receivePrepare()
{
    pduBuf.reset();
}

Status ModbusClient::receive()
{
    if (pduBuf.full())
    {
        LM(MODBUS, LW, "Client-%u, PDU buffer is full, reseting", uid);
        provideRspTimeout();
        return Status::done;
    }

    int rc = link->receive(pduBuf.end(), pduBuf.capacity());

    if (rc <= 0)
    {
        LM(MODBUS, LD, "Client-%u, receive return: %d", uid, rc);
        provideRspError();
        return Status::error;
    }

    if (trStorage.empty())
    {
        LM(MODBUS, LW, "Client-%u, received PDU is unexpected", uid);
        provideRspTimeout();
        return Status::done;
    }

    pduBuf.seek(rc);

    ModbusCodec codec(pduBuf);

    if (not codec.isPduHdrReceived())
    {
        return Status::noerror;
    }

    if (not codec.isPduReceived())
    {
        return Status::noerror;
    }

    if (not codec.isPduValid())
    {
        LM(MODBUS, LW, "Client-%u, PDU is invalid", uid);
        provideRspTimeout();
        return Status::done;
    }

    LM(MODBUS, LD, "Client-%u, RX PDU %s", uid, pduBuf.toString().c_str());

    reactor::MsgStore<ModbusClientAduRsp> msgStore;
    ModbusClientAduRsp& rsp = msgStore.getMsg();

    ModbusTcpAdu adu;
    if (not codec.decode(adu, rsp.data, rsp.numBytes))
    {
        LM(MODBUS, LW, "Client-%u, PDU decode error", uid);
        provideRspTimeout();
        return Status::done;
    }

    ModbusTransaction const& tr = trStorage.front();

    if (tr.transactId != adu.transactionId)
    {
        LM(MODBUS, LW, "Client-%u, unexpected transaction %u vs %u"
            , uid, tr.transactId, adu.transactionId);
        provideRspTimeout();
        return Status::done;
    }

    rsp.clientId = tr.clientId;
    rsp.status = MsgStatus::success;
    Sender::sendMsg(msgStore);

    trStorage.pop();

    return Status::done;
}

void ModbusClient::provideRspError(ModbusTransaction const& tr)
{
    reactor::MsgStore<ModbusClientAduRsp> msgStore;
    ModbusClientAduRsp& rsp = msgStore.getMsg();
    rsp.clientId = tr.clientId;
    rsp.status = MsgStatus::fail;
    rsp.numBytes = 0;
    Sender::sendMsg(msgStore);
}

void ModbusClient::provideRspTimeout()
{
    provideRspError(trStorage.front());
    trStorage.pop();
}

void ModbusClient::provideRspError()
{
    while (not trStorage.empty())
    {
        provideRspError(trStorage.front());
        trStorage.pop();
    }
}

void ModbusClient::start()
{
    LM(MODBUS, LD, "Client-%u, start", uid);

    fsm.getState().onStart(fsm);
}

void ModbusClient::receive(ModbusClientAduReq const& msg)
{
    ModbusTransaction tr{};
    tr.clientId = msg.clientId;
    tr.transactId = transactCounter++;
    tr.addr = msg.addr;
    tr.func = msg.func;
    tr.startReg = msg.startReg;
    tr.numRegs = msg.numRegs;
    tr.numBytes = msg.numBytes;
    tr.data = msg.data;

    if (not trStorage.push(tr))
    {
        LM(MODBUS, LE, "Client-%u, can not store transaction", tr.clientId);
        provideRspError(tr);
        return;
    }

    fsm.getState().onReceiveTransactionReq(fsm);
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

} // namespace app::modbus
