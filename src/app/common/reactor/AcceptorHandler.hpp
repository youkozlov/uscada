#pragma once

namespace reactor
{

class AcceptorHandler
{
public:
    virtual ~AcceptorHandler() {}

    virtual void onAccept() = 0;

};

} // namespace reactor
