#include "ModbusClient.hpp"
#include "LinkInterface.hpp"
#include "TimerInterface.hpp"
#include "ModbusCodec.hpp"
#include "ModbusSender.hpp"
#include "ModbusReactor.hpp"
#include "AduRespond.hpp"

#include "Logger.hpp"

namespace app::modbus
{

ModbusClient::ModbusClient(Init const& init)
    : uid(init.id)
    , addr(init.addr)
    , fsm(*this)
    , link(Reactor::get().createLink([this](auto ev){ onLinkEvent(ev); }))
    , timer(Reactor::get().createTimer([this](){ onTimerEvent(); }))
{
    pduBuf.reset();
}

ModbusClient::~ModbusClient()
{
    LM(MODBUS, LD, "~ModbusClient");
}

void ModbusClient::connect()
{
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
    if (aduStorage.empty())
    {
        return Status::noerror;
    }

    PduBuffer buf;
    ModbusCodec codec(buf);
    if (not codec.encode(aduStorage.front()))
    {
        LM(MODBUS, LE, "Client-%u, encode error", uid);
        provideRspError(aduStorage.front());
        aduStorage.pop();
        return Status::codecError;
    }

    LM(MODBUS, LD, "Client-%u, TX ADU %s", uid, buf.toString().c_str());

    int rc = link->send(buf.begin(), buf.size());
    if (rc <= 0)
    {
        LM(MODBUS, LI, "Client-%u, send return: %d", uid, rc);
        return Status::error;
    }
    return Status::done;
}

void ModbusClient::receivePreaction()
{
    pduBuf.reset();
}

Status ModbusClient::receive()
{
    if (pduBuf.size() > maxAduLen)
    {
        LM(MODBUS, LW, "Client-%u, received ADU is invalid", uid);
        return Status::done;
    }

    auto const& result = link->receive(pduBuf.end(), pduBuf.capacity());
    switch (result.status)
    {
    case reactor::LinkResult::ok:
    break;
    case reactor::LinkResult::na:
        return Status::noerror;
    case reactor::LinkResult::closed:
    case reactor::LinkResult::error:
        return Status::error;
    }

    if (aduStorage.empty())
    {
        LM(MODBUS, LW, "Client-%u, received ADU is unexpected", uid);
        return Status::done;
    }

    pduBuf.seek(result.len);

    ModbusCodec codec(pduBuf);

    if (not codec.isAduHdrReceived())
    {
        return Status::noerror;
    }

    if (not codec.isAduDataLenValid())
    {
        LM(MODBUS, LW, "Client-%u, ADU data len is invalid", uid);
        return Status::done;
    }

    if (not codec.isAduReceived())
    {
        return Status::noerror;
    }

    AduRequest const& aduReq = aduStorage.front();

    if (not codec.isAduValid())
    {
        LM(MODBUS, LW, "Client-%u, ADU is invalid", uid);
        provideRspError(aduReq);
        return Status::done;
    }

    LM(MODBUS, LD, "Client-%u, RX ADU %s", uid, pduBuf.toString().c_str());

    AduRespond aduRsp;
    if (not codec.decode(aduRsp))
    {
        LM(MODBUS, LW, "Client-%u, ADU decode error", uid);
        provideRspError(aduReq);
        return Status::done;
    }
    if (aduReq.transactId != aduRsp.transactId)
    {
        LM(MODBUS, LW, "Client-%u, unexpected transaction %u vs %u"
            , uid, aduReq.transactId, aduRsp.transactId);
        provideRspError(aduReq);
        return Status::done;
    }
    if (aduReq.addr != aduRsp.addr)
    {
        LM(MODBUS, LW, "Client-%u, unexpected slave addr %u vs %u"
            , uid, aduReq.addr, aduRsp.addr);
        provideRspError(aduReq);
        return Status::done;
    }
    if (ModbusFunction::modbusError == aduRsp.func)
    {
        LM(MODBUS, LW, "Client-%u, modbus error code (%s)"
            , uid, toString(aduRsp.error));
        provideRspModbusError(aduReq, aduRsp.error);
        return Status::done;
    }
    if (aduReq.func != aduRsp.func)
    {
        LM(MODBUS, LW, "Client-%u, unexpected function %s vs %s"
            , uid, toString(aduReq.func), toString(aduRsp.func));
        provideRspError(aduReq);
        return Status::done;
    }

    reactor::MsgStore<MsgModbusClientAduRsp> msgStore;
    MsgModbusClientAduRsp& rsp = msgStore.getMsg();
    rsp.clientId = aduReq.clientId;
    rsp.transactId = aduRsp.transactId;
    rsp.error = ModbusError::noerror;
    rsp.status = MsgStatus::success;
    rsp.numBytes = aduRsp.numBytes;
    std::memcpy(rsp.data, aduRsp.data, aduRsp.numBytes);
    Sender::sendMsg(msgStore);

    return Status::done;
}

void ModbusClient::receivePostaction()
{
    if (aduStorage.empty())
    {
        LM(MODBUS, LI, "Client-%u, ADU storage is empty", uid);
        return;
    }
    aduStorage.pop();
}

void ModbusClient::provideRspError(AduRequest const& adu)
{
    reactor::MsgStore<MsgModbusClientAduRsp> msgStore;
    MsgModbusClientAduRsp& rsp = msgStore.getMsg();
    rsp.clientId = adu.clientId;
    rsp.transactId = adu.transactId;
    rsp.error = ModbusError::noerror;
    rsp.status = MsgStatus::error;
    rsp.numBytes = 0;
    Sender::sendMsg(msgStore);
}

void ModbusClient::provideRspTimeout()
{
    if (aduStorage.empty())
    {
        LM(MODBUS, LD, "Client-%u, ADU storage is empty", uid);
        return;
    }
    provideRspError(aduStorage.front());
}

void ModbusClient::provideRspModbusError(AduRequest const& adu, ModbusError error)
{
    reactor::MsgStore<MsgModbusClientAduRsp> msgStore;
    MsgModbusClientAduRsp& rsp = msgStore.getMsg();
    rsp.clientId = adu.clientId;
    rsp.transactId = adu.transactId;
    rsp.error = error;
    rsp.status = MsgStatus::success;
    rsp.numBytes = 0;
    Sender::sendMsg(msgStore);
}

void ModbusClient::provideRspError()
{
    while (not aduStorage.empty())
    {
        provideRspError(aduStorage.front());
        aduStorage.pop();
    }
}

void ModbusClient::start()
{
    LM(MODBUS, LD, "Client-%u, start", uid);

    fsm.getState().onStart(fsm);
}

void ModbusClient::receive(ModbusClientAduReqItem const& item)
{
    AduRequest adu;
    adu.clientId = item.clientId;
    adu.transactId = item.transactId;
    adu.addr = item.addr;
    adu.func = item.func;
    adu.startItem = item.startItem;
    adu.numItems = item.numItems;
    adu.numBytes = item.numBytes;
    adu.data = const_cast<uint8_t*>(item.data);

    if (not aduStorage.push(adu))
    {
        LM(MODBUS, LE, "Client-%u, can not store transaction", adu.clientId);
        provideRspError(adu);
        return;
    }

    fsm.getState().onReceiveTransactionReq(fsm);
}

void ModbusClient::onLinkEvent(reactor::LinkEvent ev)
{
    switch (ev)
    {
    case reactor::LinkEvent::connected:
        fsm.getState().onConnected(fsm);
    break;
    case reactor::LinkEvent::data:
        fsm.getState().onDataReceived(fsm);
    break;
    case reactor::LinkEvent::error:
        fsm.getState().onError(fsm);
    break;
    }
}

void ModbusClient::onTimerEvent()
{
    fsm.getState().onTimer(fsm);
}

} // namespace app::modbus
