#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

namespace app
{

struct MsgUaSecureChannelReleaseReq : public reactor::MsgBase<MsgUaSecureChannelReleaseReq, CompIds::compUaSecChannel, MsgIds::uaSecureChannelReleaseReq>
{
};

} // namespace app
