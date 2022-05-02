#pragma once

namespace app::reactor
{

class AcceptorHandler
{
public:
    virtual ~AcceptorHandler() {}

    virtual void onAccept() = 0;

};

} // namespace app::reactor
