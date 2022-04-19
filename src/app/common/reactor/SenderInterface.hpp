#pragma once

namespace reactor
{

struct MsgInterface;

class SenderInterface
{
public:
    virtual ~SenderInterface() {}

    virtual void send(MsgInterface const&) = 0;
};

} // namespace reactor
