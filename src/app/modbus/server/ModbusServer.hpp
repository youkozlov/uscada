#pragma once

#include <vector>
#include <memory>

#include "ReactorInterface.hpp"
#include "AcceptorPtr.hpp"
#include "AcceptorHandler.hpp"
#include "ModbusSessionHandler.hpp"
#include "ModbusSessionPool.hpp"
#include "EntityId.hpp"

namespace app
{
struct ModbusAduRsp;
} // namespace app

namespace app::modbus
{

class ModbusSession;

class ModbusServer : public reactor::AcceptorHandler, public ModbusSessionHandler
{
public:
    struct Init
    {
        reactor::ReactorInterface& reactor;
        app::EntityId id;
    };
    explicit ModbusServer(Init const&);

    ~ModbusServer();

    void start();

    void stop();

    void receive(ModbusAduRsp const&);

private:

    static constexpr unsigned maxNumSession = 256;

    void onAccept() final;

    void onReleaseSession(ModbusSession::Uid) final;

    EntityId const id;
    reactor::ReactorInterface& reactor;
    reactor::AcceptorPtr acceptor;
    ModbusSessionPool sessionPool;
};

} // namespace app::modbus
