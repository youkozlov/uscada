#include "ConnectorSimple.hpp"

#include <iostream>

#include "MsgConnectorInitRsp.hpp"

namespace app
{

ConnectorSimple::ConnectorSimple(reactor::SenderInterface& sender, reactor::ReactorInterface& receiver)
    : ComponentBase(sender, receiver)
{
    registerComponent();
}

void ConnectorSimple::registerComponent()
{
    getReactor().registerHandler(
          MsgConnectorInitReq::msgId()
        , [this](reactor::MsgInterface const& msg){ receive(static_cast<MsgConnectorInitReq const&>(msg)); }
    );
}

void ConnectorSimple::receive(MsgConnectorInitReq const&)
{
    MsgConnectorInitRsp rsp;
    getSender().send(rsp);
}

} // namespace app
