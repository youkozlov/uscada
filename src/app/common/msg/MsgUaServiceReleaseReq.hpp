#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaServiceReleaseReq : public reactor::MsgBase<MsgUaServiceReleaseReq, CompIds::compUaService, MsgIds::uaServiceReleaseReq>
{
};

} // namespace app
