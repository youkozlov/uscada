#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;

#include "ReactorInterface.hpp"

namespace app::reactor
{

class ReactorMock : public ReactorInterface
{
public:
    MOCK_METHOD(void, registerHandler, (MsgId, MsgHandler), (override));
    MOCK_METHOD(void, registerHandlers, (MsgHandlerVector const&), (override));
    MOCK_METHOD(TimerPtr, createTimer, (TimerHandler), (override));
    MOCK_METHOD(LinkPtr, createLink, (LinkHandler), (override));
    MOCK_METHOD(AcceptorPtr, createAcceptor, (AcceptorHandler*), (override));
    MOCK_METHOD(void, send, (MsgInterface const&), (override));
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, stop, (), (override));
};

} // namespace app::reactor
