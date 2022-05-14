#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"
#include "MsgConnectorInitReq.hpp"

namespace app
{

class ConnectorSimple : public reactor::ComponentBase<CompIds::compConnector>
{
public:
    explicit ConnectorSimple(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(MsgConnectorInitReq const&);

private:
    void registerComponent();

};

} // namespace app
