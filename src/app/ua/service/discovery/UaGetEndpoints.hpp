#pragma once

#include "UaServiceInterface.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua::service
{

class UaGetEndpoints : public UaServiceInterface
{
public:
    UaGetEndpoints();
    ~UaGetEndpoints();

    void receive(UaEncodedMessageHdr const&, OpcUaSduBuffer&) final;
};

} // namespace app::ua::service
