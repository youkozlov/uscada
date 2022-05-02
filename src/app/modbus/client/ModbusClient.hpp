#pragma once

#include "SenderInterface.hpp"
#include "ReactorInterface.hpp"
#include "ModbusClientFsm.hpp"
#include "LinkHandler.hpp"
#include "TimerHandler.hpp"
#include "LinkInterface.hpp"
#include "TimerPtr.hpp"
#include "EntityId.hpp"
#include "ModbusError.hpp"
#include "ModbusDefs.hpp"
#include "PduBuffer.hpp"
#include "ModbusAduStorage.hpp"
#include "ModbusClientAduReq.hpp"

namespace app::modbus
{

enum class Status
{
      noerror
    , done
    , error
    , codecError
};

class ModbusClient
{
public:
    struct Init
    {
        reactor::ReactorInterface& reactor;
        app::EntityId id;
    };
    explicit ModbusClient(Init const&);

    ~ModbusClient();

    void start();

    void receive(ModbusClientAduReqItem const&);



    void connect();

    void close();

    void startTimer(long);

    void stopTimer();

    Status send();

    void receivePreaction();

    Status receive();

    void receivePostaction();

    void provideRspTimeout();

    void provideRspError();

    static constexpr long connectTimeout = 3000000;
    static constexpr long backoffTimeout = 500000;
    static constexpr long receiveTimeout = 5000000;
    static constexpr long sendDelay      = 10000;
private:

    void provideRspModbusError(AduRequest const&, ModbusError);

    void provideRspError(AduRequest const&);

    void onLinkEvent(reactor::LinkEvent);

    void onTimerEvent();

    EntityId const uid;
    reactor::ReactorInterface& reactor;
    ModbusClientFsm fsm;
    reactor::LinkPtr link;
    reactor::TimerPtr timer;
    ModbusAduStorage aduStorage;
    PduBuffer pduBuf;
};

} // namespace app::modbus
