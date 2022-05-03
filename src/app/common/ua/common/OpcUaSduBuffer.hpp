#pragma once

#include <array>
#include <cstdint>

namespace app::ua
{

class OpcUaSduBuffer
{
public:
    explicit OpcUaSduBuffer();

    ~OpcUaSduBuffer();

    void write(std::uint8_t);

    std::uint8_t read();

    std::uint8_t const* begin() const;

    std::uint8_t* begin();

    std::uint8_t* end();

    std::uint8_t const* end() const;

    std::uint32_t size() const;

    std::uint32_t capacity() const;

    void seek(std::uint32_t);

    void reset();

private:
    static constexpr unsigned maxPacketLen = 4096;

    unsigned tail;
    unsigned head;
    unsigned len;
    std::array<std::uint8_t, maxPacketLen> packet;
};

} // namespace app::ua
