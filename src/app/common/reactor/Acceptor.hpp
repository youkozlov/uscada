#pragma once

#include "LinkInterface.hpp"
#include "FileDescriptorInterface.hpp"
#include "AcceptorInterface.hpp"
#include "AcceptorHandler.hpp"

namespace reactor
{

class EpollInterface;

class Acceptor : public FileDescriptorInterface, public AcceptorInterface
{
public:
    Acceptor(EpollInterface&);

    ~Acceptor();

    void setHandler(AcceptorHandler*);

    void listen(LinkAddr const&) final;

    void accept(LinkInterface&) final;

    void close() final;

    void release() final;

private:
    int fileDescriptor() const final;

    void setFileDescriptor(int) final {}

    void onFileDescriptorEvent(int) final;

    EpollInterface& epoll;
    AcceptorHandler* handler;
    int sfd;
};

} // namespace reactor
