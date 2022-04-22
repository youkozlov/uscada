#pragma once

#include "FdHandler.hpp"

namespace reactor
{

class EpollInterface
{
public:

    virtual ~EpollInterface() {}

    virtual int add(FdHandler&, int) = 0;

    virtual int mod(FdHandler&, int) = 0;

    virtual int del(FdHandler&) = 0;
};

} // namespace reactor
