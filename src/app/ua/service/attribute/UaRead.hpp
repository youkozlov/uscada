#pragma once

#include "UaServiceInterface.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua::service
{

class UaAttributeService;

class UaRead : public UaServiceInterface
{
public:
    UaRead(UaAttributeService&);
    ~UaRead();

    void receive(UaEncodedMessageHdr const&, OpcUaSduBuffer&) final;

private:
    UaAttributeService& attributeService;
};

} // namespace app::ua::service
