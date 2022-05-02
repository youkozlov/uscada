#pragma once

#include <functional>

namespace app::reactor
{

enum class LinkEvent
{
      connected
    , data
    , error
};

using LinkHandler = std::function<void(LinkEvent)>;

/*
class LinkHandler
{
public:
    virtual ~LinkHandler() {}

    virtual void onDataReceived() = 0;

    virtual void onConnected() = 0;

    virtual void onError() = 0;
};
*/

} // namespace app::reactor
