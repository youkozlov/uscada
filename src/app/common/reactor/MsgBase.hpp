#pragma once

#include "MsgInterface.hpp"

namespace app::reactor
{

template <typename MSG_TYPE, ComponentId COMP_ID, MsgId MSG_ID>
struct MsgBase : public MsgInterface
{
    static constexpr MsgId msgId() { return MSG_ID; }

    MsgId getMsgId() const final { return MSG_ID; }

    ComponentId getCompId() const final { return COMP_ID; }

    std::size_t size() const override { return sizeof(MSG_TYPE); }
};

} // namespace app::reactor
