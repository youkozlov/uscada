#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgConnectorInitRsp : public reactor::MsgBase<MsgConnectorInitRsp, CompIds::compController, MsgIds::connectorInitRsp>
{
};

} // namespace app
