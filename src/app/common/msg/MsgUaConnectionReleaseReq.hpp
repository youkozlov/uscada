#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "UaConnectionId.hpp"

namespace app
{

struct MsgUaConnectionReleaseReq : public reactor::MsgBase<MsgUaConnectionReleaseReq, CompIds::compUaTransport, MsgIds::uaConnectionReleaseReq>
{
    UaConnectionId    connectionId;
};

} // namespace app
