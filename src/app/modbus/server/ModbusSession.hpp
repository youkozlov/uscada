#pragma once

#include "LinkPtr.hpp"
#include "LinkHandler.hpp"
#include "PduBuffer.hpp"
#include "ModbusDefs.hpp"

namespace app
{

class ModbusServer;

class ModbusSession : public reactor::LinkHandler
{
public:

    explicit ModbusSession(ModbusServer&, int);

    ~ModbusSession();

    int getId() const;

    void setLink(reactor::LinkPtr);

    reactor::LinkInterface& getLink() const;

    bool isActive() const;

    ModbusTcpAdu const& adu() const;

    PduBuffer const& pdu() const;

    void respond(ModbusTcpAdu const&);

private:

    void reset();

    void onConnected() final {}

    void onDataReceived() final;

    void onError() final {}

    void onTimer();

    int const id;
    ModbusServer& server;
    reactor::LinkPtr link;
    PduBuffer pduBuf;
    ModbusTcpAdu storedAdu;
};

} // namespace app
