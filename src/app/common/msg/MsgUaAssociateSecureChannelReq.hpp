#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "UaEncodedMessageHdr.hpp"

namespace app
{

struct MsgUaAssociateSecureChannelReq : public reactor::MsgBase<MsgUaAssociateSecureChannelReq, CompIds::compUaSecChannel, MsgIds::uaAssociateSecureChannelReq>
{
    UaEncodedMessageHdr hdr;
};

} // namespace app
