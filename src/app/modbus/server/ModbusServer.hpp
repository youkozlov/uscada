#pragma once

#include <vector>
#include <memory>

#include "ReactorInterface.hpp"
#include "AcceptorPtr.hpp"
#include "AcceptorHandler.hpp"
#include "ModbusSessionHandler.hpp"
#include "ModbusSessionPool.hpp"
#include "EntityId.hpp"
#include "LinkAddr.hpp"
#include "MsgModbusAduRsp.hpp"

namespace app::modbus
{

class ModbusSession;

class ModbusServer : public reactor::AcceptorHandler, public ModbusSessionHandler
{
public:
    struct Init
    {
        app::EntityId id;
        reactor::LinkAddr const& addr;
    };
    explicit ModbusServer(Init const&);

    ~ModbusServer();

    void start();

    void stop();

    void receive(MsgModbusAduRsp const&);

private:

    static constexpr unsigned maxNumSession = 256;

    void onAcceptEvent();

    void onReleaseSession(ModbusSession::Uid) final;

    EntityId const id;
    reactor::LinkAddr addr;
    reactor::AcceptorPtr acceptor;
    ModbusSessionPool sessionPool;
};

} // namespace app::modbus
