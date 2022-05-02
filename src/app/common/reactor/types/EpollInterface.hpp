#pragma once

#include "FileDescriptorInterface.hpp"

namespace reactor
{

class EpollInterface
{
public:

    virtual ~EpollInterface() {}

    virtual int add(FileDescriptorInterface&, int) = 0;

    virtual int mod(FileDescriptorInterface&, int) = 0;

    virtual int del(FileDescriptorInterface&) = 0;
};

} // namespace reactor
