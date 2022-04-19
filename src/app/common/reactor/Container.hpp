#pragma once

#include <string>

#include "ComponentId.hpp"

namespace reactor
{

struct Container
{
    std::vector<reactor::ComponentId> components;
    uint64_t numThreads;
    uint64_t cpuMask;
};


} // namespace reactor
