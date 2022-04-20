#pragma once

#include "PipeEvent.hpp"

namespace reactor
{

class PipeHandler
{
public:
    virtual ~PipeHandler() {}

    virtual void onPipeEvent(PipeEvent const&) = 0;
};


} // namespace reactor
