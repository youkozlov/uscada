#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;

#include "TimerInterface.hpp"

namespace app::reactor
{

class TimerMock : public TimerInterface
{
public:
    MOCK_METHOD(void, start, (long), (override));
    MOCK_METHOD(void, stop, (), (override));
    MOCK_METHOD(void, release, (), (override));
};

} // namespace app::reactor
