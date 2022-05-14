#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "UaEncodedMessageHdr.hpp"

namespace app
{

struct MsgUaEncodedMessageReceiveInd : public reactor::MsgBase<MsgUaEncodedMessageReceiveInd, CompIds::compUaService, MsgIds::uaEncodedMessageReceiveInd>
{
    UaEncodedMessageHdr hdr;
    std::uint32_t       length;
    std::uint8_t        data[];

    std::size_t size() const final
    {
        return sizeof(MsgUaEncodedMessageReceiveInd) + length;
    }
};

} // namespace app
