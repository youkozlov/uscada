#pragma once

namespace app::ua
{

class OpcUaSecureChannel;

class UaServiceInterface
{
public:
    virtual ~UaServiceInterface() {}

    virtual void process(OpcUaSecureChannel&) = 0;
};

} // namespace app::ua
