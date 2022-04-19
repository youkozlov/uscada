#pragma once

#include "CompDefs.hpp"
#include "ComponentBase.hpp"

namespace app
{

struct ConnectorInitReq;

class ConnectorSimple : public reactor::ComponentBase<CompIds::connector>
{
public:
    explicit ConnectorSimple(reactor::SenderInterface&, reactor::ReactorInterface&);

    void receive(ConnectorInitReq const&);

private:
    void registerComponent();

};

} // namespace app
