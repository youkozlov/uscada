#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaTransportInitReq : public reactor::MsgBase<MsgUaTransportInitReq, CompIds::compUaTransport, MsgIds::uaTransportInitReq>
{
};

} // namespace app
