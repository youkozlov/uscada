#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaTransportConfigRsp : public reactor::MsgBase<MsgUaTransportConfigRsp, CompIds::compController, MsgIds::uaTransportConfigRsp>
{
};

} // namespace app
