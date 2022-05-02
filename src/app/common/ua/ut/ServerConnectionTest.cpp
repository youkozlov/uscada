#include "gtest/gtest.h"

#include "ReactorMock.hpp"
#include "TimerMock.hpp"
#include "LinkMock.hpp"
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
        EXPECT_CALL(reactorMock, createLink(_)).WillOnce(Return(ByMove(reactor::LinkPtr(&linkMock, [](auto){}))));
        EXPECT_CALL(reactorMock, createTimer(_)).WillOnce(Return(ByMove(reactor::TimerPtr(&timerMock, [](auto){}))));
        server = std::make_unique<ServerConnection>(reactorMock);
    }
    void connect()
    {
        EXPECT_CALL(timerMock, start(_));
        EXPECT_CALL(linkMock, connect(_));
        server->connect();
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
        std::uint8_t values[32] = {0, 0, 0, 0, 24};
        EXPECT_CALL(linkMock, receive(_,_)).WillOnce(DoAll(SetArrayArgument<0>(values, values + 32), Return(32)));
        EXPECT_CALL(timerMock, stop());
        EXPECT_CALL(linkMock, send(_, 28)).WillOnce(Return(28));
        EXPECT_CALL(timerMock, start(_));
        server->onLinkEvent(reactor::LinkEvent::data);
    }

protected:
    reactor::ReactorMock reactorMock;
    reactor::TimerMock timerMock;
    reactor::LinkMock linkMock;
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

    EXPECT_CALL(linkMock, receive(_,_)).WillOnce(Return(0));
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