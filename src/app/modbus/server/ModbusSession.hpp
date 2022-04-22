#pragma once

#include "LinkPtr.hpp"
#include "TimerPtr.hpp"
#include "LinkHandler.hpp"
#include "TimerHandler.hpp"
#include "PduBuffer.hpp"
#include "ModbusDefs.hpp"

namespace app::modbus
{

class ModbusSessionHandler;

class ModbusSession : public reactor::LinkHandler, public reactor::TimerHandler
{
public:

    explicit ModbusSession(ModbusSessionHandler &, int);

    ~ModbusSession();

    int getId() const;

    void setLink(reactor::LinkPtr);

    void setTimer(reactor::TimerPtr);

    reactor::LinkInterface& getLink() const;

    ModbusTcpAdu const& adu() const;

    PduBuffer const& pdu() const;

    void respond(ModbusTcpAdu const&, void const*, unsigned);

    void respondError(ModbusTcpAdu const&, ModbusErorr);

private:

    static constexpr long timeout = 60000000;

    void reset();

    void remove();

    void onConnected() final {}

    void onDataReceived() final;

    void onError() final {}

    void onTimer() final;

    int const id;
    ModbusSessionHandler &handler;
    reactor::TimerPtr timer;
    reactor::LinkPtr link;
    PduBuffer pduBuf;
    ModbusTcpAdu storedAdu;
};

} // namespace app::modbus
