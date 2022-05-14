#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "LinkAddr.hpp"

namespace app
{

struct MsgUaTransportConfigReq : public reactor::MsgBase<MsgUaTransportConfigReq, CompIds::compUaTransport, MsgIds::uaTransportConfigReq>
{
    reactor::LinkAddr addr;
};

} // namespace app
