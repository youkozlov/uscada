#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;

#include "OpcUaConnection.hpp"

namespace app::ua
{

class OpcUaConnectionHandlerMock : public OpcUaConnectionHandler
{
public:
    MOCK_METHOD(void, onConnectionConnectedEvent, (), (override));
    MOCK_METHOD(void, onConnectionDataReceivedEvent, (), (override));
    MOCK_METHOD(void, onConnectionErrorEvent, (), (override));
    MOCK_METHOD(void, onConnectionClosedEvent, (), (override));
};

} // namespace app::reactor
