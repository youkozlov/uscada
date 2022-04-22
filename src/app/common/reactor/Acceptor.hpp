#pragma once

#include "LinkInterface.hpp"
#include "AcceptorInterface.hpp"
#include "AcceptorHandler.hpp"

namespace reactor
{

class EpollInterface;

class Acceptor : public FdHandler, public AcceptorInterface
{
public:
    Acceptor(EpollInterface&, AcceptorHandler&);

    ~Acceptor();

    int getFd() const final;

    void onEvent(int) final;

    void listen(LinkAddr const&) final;

    void accept(LinkInterface&) final;

    void close() final;

private:
    EpollInterface& epoll;
    AcceptorHandler& handler;
    int sfd;
};

} // namespace reactor
