#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaServiceReleaseRsp : public reactor::MsgBase<MsgUaServiceReleaseRsp, CompIds::compUaSecChannel, MsgIds::uaServiceReleaseRsp>
{
};

} // namespace app
