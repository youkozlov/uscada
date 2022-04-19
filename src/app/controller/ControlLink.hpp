#pragma once

#include "LinkHandler.hpp"
#include "ReactorInterface.hpp"
#include "LinkInterface.hpp"

namespace app
{

class ControlLink : public reactor::LinkHandler
{
public:
    explicit ControlLink(reactor::ReactorInterface&);

    ~ControlLink();

    void onDataReceived() final;

    void onConnected() final;

    void onError() final;

    void connect();

private:
    reactor::LinkInterface& link;
};

} // namespace app
