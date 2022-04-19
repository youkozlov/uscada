#include "ControlLink.hpp"
#include <iostream>

namespace app
{

ControlLink::ControlLink(reactor::ReactorInterface& reactor)
    : link(*reactor.createLink(*this))
{
}

ControlLink::~ControlLink()
{
}

void ControlLink::onDataReceived()
{
    std::cout << "onDataReceived" << std::endl;
}

void ControlLink::onConnected()
{
    std::cout << "onConnected" << std::endl;
    link.send("AAA\n", 5);
}

void ControlLink::onError()
{
    std::cout << "onError" << std::endl;
}

void ControlLink::connect()
{
    reactor::LinkAddr addr;
    link.connect(addr);
}

} // namespace app
