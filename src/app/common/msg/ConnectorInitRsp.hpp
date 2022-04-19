#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct ConnectorInitRsp : public reactor::MsgBase<ConnectorInitRsp, CompIds::controller, MsgIds::connectorInitRsp>
{
};

} // namespace app