#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaTransportReleaseRsp : public reactor::MsgBase<MsgUaTransportReleaseRsp, CompIds::compController, MsgIds::uaTransportReleaseRsp>
{
};

} // namespace app
