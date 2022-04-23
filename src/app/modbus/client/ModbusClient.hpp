#pragma once

#include "SenderInterface.hpp"
#include "ReactorInterface.hpp"
#include "ModbusClientFsm.hpp"
#include "LinkHandler.hpp"
#include "TimerHandler.hpp"
#include "LinkInterface.hpp"
#include "TimerPtr.hpp"
#include "EntityId.hpp"
#include "ModbusDefs.hpp"
#include "PduBuffer.hpp"
#include "ModbusTransactionStorage.hpp"

namespace app
{
struct ModbusClientAduReq;
}

namespace app::modbus
{

enum class Status
{
      noerror
    , done
    , error
};

class ModbusClient : public reactor::LinkHandler, public reactor::TimerHandler
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

    void receive(ModbusClientAduReq const&);



    void connect();

    void close();

    void startTimer(long);

    void stopTimer();

    Status send();

    void receivePrepare();

    Status receive();

    void provideRspTimeout();

    void provideRspError();

    static constexpr long connectTimeout = 3000000;
    static constexpr long backoffTimeout = 500000;
    static constexpr long receiveTimeout = 5000000;
private:

    void provideRspError(ModbusTransaction const&);

    void onConnected() final;

    void onDataReceived() final;

    void onError() final;

    void onTimer() final;

    app::EntityId const uid;
    reactor::ReactorInterface& reactor;
    ModbusClientFsm fsm;
    reactor::LinkPtr link;
    reactor::TimerPtr timer;
    ModbusTransactionStorage trStorage;
    PduBuffer pduBuf;
    TransactId transactCounter;
};

} // namespace app::modbus
