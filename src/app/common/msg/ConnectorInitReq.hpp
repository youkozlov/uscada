#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ConnectorInitReq : public reactor::MsgBase<ConnectorInitReq, CompIds::connector, MsgIds::connectorInitReq>
{
};

} // namespace app
