#include "gtest/gtest.h"

#include "ReactorMock.hpp"
#include "TimerMock.hpp"
#include "LinkMock.hpp"
#include "OpcUaConnectionHandlerMock.hpp"
#include "ServerConnection.hpp"

using ::testing::Return;
using ::testing::ByMove;
using ::testing::DoAll;
using ::testing::SetArrayArgument;

using namespace app;
using namespace app::ua;

class ServerConnectionTest : public ::testing::Test
{
public:
    void init()
    {
        server = std::make_unique<ServerConnection>(reactorMock, handlerMock);
    }
    void connect()
    {
        EXPECT_CALL(reactorMock, createLink(_)).WillOnce(Return(ByMove(reactor::LinkPtr(&linkMock, [](auto){}))));
        EXPECT_CALL(reactorMock, createTimer(_)).WillOnce(Return(ByMove(reactor::TimerPtr(&timerMock, [](auto){}))));
        EXPECT_CALL(timerMock, start(_));
        EXPECT_CALL(linkMock, connect(_));
        reactor::LinkAddr addr;
        server->connect(addr);
    }
    void connected()
    {
        EXPECT_CALL(linkMock, send(_, 16)).WillOnce(Return(16));
        EXPECT_CALL(timerMock, stop());
        EXPECT_CALL(timerMock, start(_));
        server->onLinkEvent(reactor::LinkEvent::connected);
    }
    void receiveHello()
    {
        reactor::LinkResult result{reactor::LinkResult::ok, 32};
        std::uint8_t values[32] = {'H', 'E', 'L', 'F', 32};
        EXPECT_CALL(linkMock, receive(_,_)).WillOnce(DoAll(SetArrayArgument<0>(values, values + 32), Return(result)));
        EXPECT_CALL(timerMock, stop());
        EXPECT_CALL(linkMock, send(_, 28)).WillOnce(Return(28));
        EXPECT_CALL(timerMock, start(_));
        server->onLinkEvent(reactor::LinkEvent::data);
    }

protected:
    reactor::ReactorMock reactorMock;
    reactor::TimerMock timerMock;
    reactor::LinkMock linkMock;
    ua::OpcUaConnectionHandlerMock handlerMock;
    std::unique_ptr<ServerConnection> server;
};

TEST_F(ServerConnectionTest, Init)
{
    init();
}

TEST_F(ServerConnectionTest, ConnectTimeout)
{
    init();
    connect();

    EXPECT_CALL(linkMock, close());
    EXPECT_CALL(timerMock, stop());
    server->onTimerEvent();
}

TEST_F(ServerConnectionTest, Connected)
{
    init();
    connect();
    connected();
}

TEST_F(ServerConnectionTest, ReceiveHelloTimeout)
{
    init();
    connect();
    connected();

    EXPECT_CALL(linkMock, close());
    EXPECT_CALL(timerMock, stop());
    server->onTimerEvent();
}

TEST_F(ServerConnectionTest, ReceiveHelloClose)
{
    init();
    connect();
    connected();

    reactor::LinkResult result{reactor::LinkResult::error, 0};
    EXPECT_CALL(linkMock, receive(_,_)).WillOnce(Return(result));
    EXPECT_CALL(linkMock, close());
    EXPECT_CALL(timerMock, stop());
    server->onLinkEvent(reactor::LinkEvent::data);
}

TEST_F(ServerConnectionTest, ReceiveHello)
{
    init();
    connect();
    connected();
    receiveHello();
}