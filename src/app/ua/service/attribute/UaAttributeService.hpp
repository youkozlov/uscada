#pragma once

#include "UaReadReq.hpp"
#include "UaEncodedMessageHdr.hpp"

namespace app::ua::service
{

class UaService;

class UaAttributeService
{
public:
    UaAttributeService();
    ~UaAttributeService();

    void subscribe(UaService&);

    void receive(UaEncodedMessageHdr const&, UaReadReq const&);

private:
};

} // namespace app::ua::service
