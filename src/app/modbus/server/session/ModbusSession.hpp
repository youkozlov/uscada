#pragma once

#include <array>
#include <cstdint>

#include "LinkPtr.hpp"
#include "TimerPtr.hpp"
#include "LinkHandler.hpp"
#include "TimerHandler.hpp"
#include "PduBuffer.hpp"
#include "ModbusDefs.hpp"
#include "ModbusSessionFsm.hpp"
#include "ModbusAduRsp.hpp"
#include "AduRequest.hpp"

namespace app::modbus
{

enum class Result
{
      noerror
    , done
    , error
    , codecError
};

class ModbusSessionHandler;

class ModbusSession
{
public:

    using Uid = unsigned;

    explicit ModbusSession(ModbusSessionHandler&, Uid);

    ~ModbusSession();

    void prepare(EntityId);

    reactor::LinkInterface& getLink();

    void start();

    void receive(ModbusAduRsp const&);



    void startTimer(long);

    void stopTimer();

    void receivePreaction();

    Result receive();

    Result send(ModbusAduRsp const&);

    void releaseSession();

    static constexpr long inactiveTimeout = 30000000;
    static constexpr long aduRspTimeout = 5000000;

private:

    void onLinkEvent(reactor::LinkEvent);

    void onTimerEvent();

    Uid const uid;
    EntityId serverId;
    ModbusSessionFsm fsm;
    ModbusSessionHandler &handler;
    reactor::TimerPtr timer;
    reactor::LinkPtr link;
    PduBuffer pduBuf;
    std::array<std::uint8_t, maxAduLen> storedAduBuf;
    AduRequest storedAdu;
};

} // namespace app::modbus
