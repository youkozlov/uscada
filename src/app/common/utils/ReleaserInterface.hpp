#pragma once

#include "EntityId.hpp"

namespace app
{

class ReleaserInterface
{
public:
    virtual ~ReleaserInterface() {}

    virtual void release(EntityId) = 0;
};

} // namespace app
