#pragma once

#include "ComponentId.hpp"

namespace reactor
{

class SenderInterface;
class ReactorInterface;

class ComponentInterface
{
public:
    virtual ~ComponentInterface() {}

    virtual ComponentId getCompId() const = 0;

    virtual SenderInterface& getSender() = 0;

    virtual ReactorInterface& getReactor() = 0;
};

} // namespace reactor
