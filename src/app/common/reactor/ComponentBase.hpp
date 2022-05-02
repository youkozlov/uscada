#pragma once

#include "ComponentInterface.hpp"
#include "ReactorInterface.hpp"
#include "SenderInterface.hpp"

namespace app::reactor
{

template<ComponentId COMP_ID>
class ComponentBase : public ComponentInterface
{
public:
    ComponentBase(SenderInterface& sender_, ReactorInterface& reactor_)
        : sender(sender_)
        , reactor(reactor_)
    {}

    SenderInterface& getSender() final { return sender; }

    ReactorInterface& getReactor() final { return reactor; }

    ComponentId getCompId() const final { return COMP_ID; }

private:
    SenderInterface& sender;
    ReactorInterface& reactor;
};

} // namespace app::reactor
