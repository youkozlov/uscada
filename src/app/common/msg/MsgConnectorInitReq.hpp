#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgConnectorInitReq : public reactor::MsgBase<MsgConnectorInitReq, CompIds::compConnector, MsgIds::connectorInitReq>
{
};

} // namespace app
