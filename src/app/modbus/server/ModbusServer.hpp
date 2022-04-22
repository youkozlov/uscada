#pragma once

#include <vector>
#include <memory>

#include "ReactorInterface.hpp"
#include "AcceptorPtr.hpp"
#include "AcceptorHandler.hpp"
#include "ModbusSessionHandler.hpp"
#include "ModbusSessionPool.hpp"
#include "ModbusAduPool.hpp"

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
    explicit ModbusServer(reactor::ReactorInterface&);

    ~ModbusServer();

    void start();

    void stop();

    void receive(ModbusAduRsp const&);

private:

    void createSession();

    void onAccept() final;

    void onRemoveSession(ModbusSession&) final;

    void onAduReceived(ModbusSession&) final;

    reactor::ReactorInterface& reactor;
    reactor::AcceptorPtr acceptor;
    ModbusSessionPool sessionPool;
    ModbusAduPool aduPool;
};

} // namespace app::modbus
