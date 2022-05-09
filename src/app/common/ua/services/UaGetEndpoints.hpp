#pragma once

#include "UaServiceInterface.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

class UaGetEndpoints : public UaServiceInterface
{
public:
    UaGetEndpoints();
    ~UaGetEndpoints();

    void process(OpcUaSecureChannel&) final;

private:
    void response(OpcUaSecureChannel&);

    std::uint32_t storedRequestHandle;
};

} // namespace app::ua
