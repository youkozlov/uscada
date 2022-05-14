#pragma once

#include "CompDefs.hpp"
#include "MsgDefs.hpp"
#include "MsgBase.hpp"

#include "UaConnectionId.hpp"
#include "UaSecureChannelId.hpp"
#include "UaChunkType.hpp"

namespace app
{

struct MsgUaCloseSecureChannelRsp : public reactor::MsgBase<MsgUaCloseSecureChannelRsp, CompIds::compUaTransport, MsgIds::uaCloseSecureChannelRsp>
{
    UaConnectionId      connectionId;
    UaSecureChannelId   secureChannelId;
    UaChunkType         chunkType;

    std::uint32_t       length;
    std::uint8_t        data[];

    std::size_t size() const final
    {
        return sizeof(MsgUaCloseSecureChannelRsp) + length;
    }
};

} // namespace app
