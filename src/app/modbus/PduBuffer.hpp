#pragma once

#include <cstring>

namespace app
{

class PduBuffer
{

static constexpr unsigned maxLen = 512;

public:
    explicit PduBuffer()
        : pos(0)
        , len(0)
    {}

    unsigned char const* begin() const
    {
        return &buf[0];
    }

    unsigned char* begin()
    {
        return &buf[0];
    }

    unsigned char* end()
    {
        return &buf[len];
    }

    unsigned read()
    {
        return buf[pos++];
    }
    
    unsigned readLe()
    {
        unsigned ll = buf[pos++];
        unsigned hh = buf[pos++];
        return (hh << 8) | ll;
    }

    unsigned readBe()
    {
        unsigned hh = buf[pos++];
        unsigned ll = buf[pos++];
        return (hh << 8) | ll;
    }
    
    void write(unsigned ch)
    {
        buf[len++] = ch;
    }

    void writeBe(unsigned ch)
    {
        buf[len++] = ch >> 8;
        buf[len++] = ch;
    }

    void seek(unsigned val)
    {
        len += val;
    }

    unsigned size() const
    {
        return len;
    }

    unsigned capacity() const
    {
        return maxLen - len;
    }

    void reset()
    {
        len = 0;
        pos = 0;
    }

private:
    unsigned char buf[maxLen];
    unsigned pos;
    unsigned len;
};
}