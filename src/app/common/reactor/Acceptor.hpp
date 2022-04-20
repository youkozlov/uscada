#pragma once

#include "LinkInterface.hpp"
#include "AcceptorInterface.hpp"
#include "AcceptorHandler.hpp"
#include "Epoll.hpp"

namespace reactor
{

class Acceptor : public FdHandler, public AcceptorInterface
{
public:
    Acceptor(AcceptorHandler&, Epoll&);

    ~Acceptor();

    int getFd() const final;

    void onEvent(int) final;

    void listen(LinkAddr const&) final;

    void accept(LinkInterface&) final;

    void close() final;

private:
    AcceptorHandler& handler;
    Epoll& epoll;
    int sfd;
};

} // namespace reactor
