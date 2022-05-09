#pragma once

#include <map>
#include <memory>

#include "OpcUaServerSecureChannel.hpp"
#include "ServerConnection.hpp"
#include "AcceptorPtr.hpp"
#include "DataType.hpp"
#include "UaServiceInterface.hpp"
#include "UaEntityPool.hpp"
#include "UaSessionController.hpp"
#include "UaAttributeController.hpp"

namespace app::ua
{

class OpcUaServer
{
public:
    OpcUaServer(reactor::ReactorInterface&);

    ~OpcUaServer();

    void listen(reactor::LinkAddr& addr);

    void onAcceptEvent();

    void onSecureChannelEvent(OpcUaSecureChannelEvent const&);

private:

    void onSecureChannelReq(OpcUaSecureChannel&);

    void onSecureChannelRelease(OpcUaSecureChannel&);

    reactor::ReactorInterface& reactor;
    reactor::AcceptorPtr acceptor;
    UaEntityPool<OpcUaServerSecureChannel> channelPool;
    UaSessionController sessionController;
    UaAttributeController attributeController;
    std::map<DataTypeId, std::unique_ptr<UaServiceInterface>> services;
};

} // namespace app::ua
