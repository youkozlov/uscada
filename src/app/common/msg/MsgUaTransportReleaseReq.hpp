#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaTransportReleaseReq : public reactor::MsgBase<MsgUaTransportReleaseReq, CompIds::compUaTransport, MsgIds::uaTransportReleaseReq>
{
};

} // namespace app
