#pragma once

#include "MsgStore.hpp"
#include "Logger.hpp"

namespace reactor
{

template <typename SENDER>
class SenderBase
{
public:
    SenderBase(SenderBase&) = delete;
    SenderBase& operator=(SenderBase const&) = delete;
    SenderBase()
    {
        sender = reinterpret_cast<SENDER*>(this);
    }
    virtual ~SenderBase() {}

    template <typename MSG_TYPE>
    static void sendMsg(MsgStore<MSG_TYPE> const& store)
    {
        if (not sender)
        {
            LM(GEN, LE, "Msg sender is undefined");
            return;
        }
        sender->send(store.getMsg());
    }
private:
    static SENDER* sender;
};

template <typename SENDER>
SENDER* SenderBase<SENDER>::sender = nullptr;

} // namespace reactor
