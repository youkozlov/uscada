#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;

#include "LinkInterface.hpp"

namespace app::reactor
{

class LinkMock : public LinkInterface
{
public:
    MOCK_METHOD(int, fileDescriptor, (), (const));
    MOCK_METHOD(void, setFileDescriptor, (int), (override));
    MOCK_METHOD(void, onFileDescriptorEvent, (int), (override));
    MOCK_METHOD(void, connect, (LinkAddr const&), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(void, release, (), (override));
    MOCK_METHOD(int, send, (void const*, std::size_t), (override));
    MOCK_METHOD(LinkResult, receive, (std::uint8_t*, std::size_t), (override));
};

} // namespace app::reactor
