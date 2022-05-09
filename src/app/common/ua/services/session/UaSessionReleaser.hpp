#pragma once

#include "EntityId.hpp"

namespace app::ua
{

class UaSessionReleaser
{
public:
    virtual ~UaSessionReleaser() {}

    virtual void releaseSession(EntityId) = 0;
};

} // namespace app::ua
