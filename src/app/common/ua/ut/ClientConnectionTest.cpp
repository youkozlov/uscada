#include "gtest/gtest.h"

#include "ReactorMock.hpp"
#include "TimerMock.hpp"
#include "LinkMock.hpp"
#include "ClientConnection.hpp"

using ::testing::Return;
using ::testing::ByMove;
using ::testing::DoAll;
using ::testing::SetArrayArgument;

using namespace app;
using namespace app::ua;

class ClientConnectionTest : public ::testing::Test
{
public:
    void init()
    {
        client = std::make_unique<ClientConnection>(reactorMock);
    }
    void connect()
    {
        EXPECT_CALL(reactorMock, createLink(_)).WillOnce(Return(ByMove(reactor::LinkPtr(&linkMock, [](auto){}))));
        EXPECT_CALL(reactorMock, createTimer(_)).WillOnce(Return(ByMove(reactor::TimerPtr(&timerMock, [](auto){}))));
        EXPECT_CALL(timerMock, start(_));
        EXPECT_CALL(linkMock, connect(_));
        reactor::LinkAddr addr;
        client->connect(addr);
    }
    void connected()
    {
        EXPECT_CALL(linkMock, send(_, 32)).WillOnce(Return(16));
        EXPECT_CALL(timerMock, stop());
        EXPECT_CALL(timerMock, start(_));
        client->onLinkEvent(reactor::LinkEvent::connected);
    }
    void receiveAck()
    {
        reactor::LinkResult result{reactor::LinkResult::ok, 28};
        std::uint8_t values[28] = {'A', 'C', 'K', 'F', 28};
        EXPECT_CALL(linkMock, receive(_,_)).WillOnce(DoAll(SetArrayArgument<0>(values, values + 28), Return(result)));
        EXPECT_CALL(timerMock, stop());
        EXPECT_CALL(timerMock, start(_));
        client->onLinkEvent(reactor::LinkEvent::data);
    }

protected:
    reactor::ReactorMock reactorMock;
    reactor::TimerMock timerMock;
    reactor::LinkMock linkMock;
    std::unique_ptr<ClientConnection> client;
};

TEST_F(ClientConnectionTest, Init)
{
    init();
}

TEST_F(ClientConnectionTest, ConnectTimeout)
{
    init();
    connect();

    EXPECT_CALL(linkMock, close());
    EXPECT_CALL(timerMock, stop());
    client->onTimerEvent();
}

TEST_F(ClientConnectionTest, Connected)
{
    init();
    connect();
    connected();
}

TEST_F(ClientConnectionTest, ReceiveAckTimeout)
{
    init();
    connect();
    connected();

    EXPECT_CALL(linkMock, close());
    EXPECT_CALL(timerMock, stop());
    client->onTimerEvent();
}

TEST_F(ClientConnectionTest, ReceiveAckClose)
{
    init();
    connect();
    connected();

    reactor::LinkResult result{reactor::LinkResult::error, 0};
    EXPECT_CALL(linkMock, receive(_,_)).WillOnce(Return(result));
    EXPECT_CALL(linkMock, close());
    EXPECT_CALL(timerMock, stop());
    client->onLinkEvent(reactor::LinkEvent::data);
}

TEST_F(ClientConnectionTest, ReceiveHello)
{
    init();
    connect();
    connected();
    receiveAck();
}