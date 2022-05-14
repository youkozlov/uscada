#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "UaEncodedMessageHdr.hpp"

namespace app
{

struct MsgUaEncodedMessageSendReq : public reactor::MsgBase<MsgUaEncodedMessageSendReq, CompIds::compUaSecChannel, MsgIds::uaEncodedMessageSendReq>
{
    UaEncodedMessageHdr hdr;
    std::uint32_t       length;
    std::uint8_t        data[];

    std::size_t size() const final
    {
        return sizeof(MsgUaEncodedMessageSendReq) + length;
    }
};

} // namespace app
