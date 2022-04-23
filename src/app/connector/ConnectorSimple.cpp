#include "ConnectorSimple.hpp"

#include <iostream>

#include "ConnectorInitReq.hpp"
#include "ConnectorInitRsp.hpp"

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
          ConnectorInitReq::msgId()
        , [this](reactor::MsgInterface const& msg){ receive(static_cast<ConnectorInitReq const&>(msg)); }
    );
}

void ConnectorSimple::receive(ConnectorInitReq const&)
{
    ConnectorInitRsp rsp;
    getSender().send(rsp);
}

} // namespace app
