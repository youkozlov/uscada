#pragma once

#include <vector>
#include <memory>

#include "SenderInterface.hpp"
#include "ReactorInterface.hpp"
#include "AcceptorPtr.hpp"
#include "AcceptorHandler.hpp"
#include "ModbusSessionPool.hpp"
#include "ModbusAduPool.hpp"

namespace app
{

class ModbusSession;
struct ModbusAduRsp;

class ModbusServer : public reactor::AcceptorHandler
{
public:
    explicit ModbusServer(reactor::SenderInterface&, reactor::ReactorInterface&);

    ~ModbusServer();

    void start();

    void receive(ModbusAduRsp const&);

    void createSession();

    void removeSession(ModbusSession&);

    void onAduReceived(ModbusSession&);

private:

    void onAccept() final;

    reactor::SenderInterface& sender;
    reactor::ReactorInterface& reactor;
    reactor::AcceptorPtr acceptor;
    ModbusSessionPool sessionPool;
    ModbusAduPool aduPool;
};

} // namespace app
