#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaTransportInitRsp : public reactor::MsgBase<MsgUaTransportInitRsp, CompIds::compController, MsgIds::uaTransportInitRsp>
{
};

} // namespace app
