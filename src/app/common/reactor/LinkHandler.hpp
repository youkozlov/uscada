#pragma once

namespace reactor
{

class LinkHandler
{
public:
    virtual ~LinkHandler() {}

    virtual void onDataReceived() = 0;

    virtual void onConnected() = 0;

    virtual void onError() = 0;
};

} // namespace reactor
