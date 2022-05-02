#pragma once

#include "MaxMsgSize.hpp"

namespace app::reactor
{

template <typename MSG_TYPE>
class MsgStore
{
public:
    MsgStore()
        : msg(*(new (&buf[0]) MSG_TYPE))
    {
        static_assert(sizeof(MSG_TYPE) <= reactor::maxMsgSize, "Msg buffer too small");
    }
    MSG_TYPE& getMsg()
    {
        return msg;
    }
    MSG_TYPE const& getMsg() const
    {
        return msg;
    }
private:
    MSG_TYPE& msg;
    unsigned char buf[reactor::maxMsgSize];
};


} // namespace app
