#pragma once

#include "OpcUaBinaryStream.hpp"

namespace ua
{

class OpcUaBinaryCodec
{
public:
    OpcUaBinaryCodec(OpcUaBinaryStream&);
    ~OpcUaBinaryCodec();

    void encode();

    void decode();

private:
    OpcUaBinaryStream stream;
};

} // namespace ua
