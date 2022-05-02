#pragma once

namespace app::reactor
{

class FileDescriptorInterface
{
public:

    virtual ~FileDescriptorInterface() {}

    virtual int fileDescriptor() const = 0;

    virtual void setFileDescriptor(int) = 0;

    virtual void onFileDescriptorEvent(int) = 0;
};

} // namespace app::reactor
