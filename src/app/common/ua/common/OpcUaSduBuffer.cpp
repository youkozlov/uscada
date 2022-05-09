#include "OpcUaSduBuffer.hpp"
#include "Logger.hpp"

namespace app::ua
{

OpcUaSduBuffer::OpcUaSduBuffer()
    : tail(0)
    , head(0)
{
}

OpcUaSduBuffer::~OpcUaSduBuffer()
{
}

void OpcUaSduBuffer::write(std::uint8_t val)
{
    //LM(GEN, LE, "end: %u, wr: %d", head, (int)val);
    packet[head++] = val;
}

std::uint8_t OpcUaSduBuffer::read()
{
    auto const& rd = packet[tail];
    //LM(GEN, LE, "tail: %u, rd: %d", tail, (int)rd);
    tail++;
    return rd;
}

std::uint8_t const* OpcUaSduBuffer::begin() const
{
    return &packet[tail];
}

std::uint8_t* OpcUaSduBuffer::begin()
{
    return &packet[tail];
}

std::uint8_t* OpcUaSduBuffer::end()
{
    return &packet[head];
}

std::uint8_t const* OpcUaSduBuffer::end() const
{
    return &packet[head];
}

std::uint32_t OpcUaSduBuffer::size() const
{
    return head;
}

std::uint32_t OpcUaSduBuffer::capacity() const
{
    return maxPacketLen - head;
}

void OpcUaSduBuffer::seek(std::uint32_t val)
{
    head += val;
}

void OpcUaSduBuffer::reset()
{
    tail = head = 0;
}

} // namespace app::ua
