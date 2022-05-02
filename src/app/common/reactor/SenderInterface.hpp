#pragma once

namespace app::reactor
{

struct MsgInterface;

class SenderInterface
{
public:
    virtual ~SenderInterface() {}

    virtual void send(MsgInterface const&) = 0;
};

} // namespace app::reactor
