#pragma once

#include "UaServiceInterface.hpp"


namespace app::ua::service
{

class UaAttributeService;
class UaSessionService;

class UaRead : public UaServiceInterface
{
public:
    UaRead(UaAttributeService&, UaSessionService&);
    ~UaRead();

    void receive(UaEncodedMessageHdr const&, OpcUaSduBuffer&) final;

private:
    UaAttributeService& attributeService;
    UaSessionService& sessionService;
};

} // namespace app::ua::service
