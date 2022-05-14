#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaServiceInitRsp : public reactor::MsgBase<MsgUaServiceInitRsp, CompIds::compUaSecChannel, MsgIds::uaServiceInitRsp>
{
};

} // namespace app
