#pragma once

#include <memory>
#include "OpcUaSduBuffer.hpp"
#include "UaEncodedMessageHdr.hpp"

namespace app::ua::service
{

class UaServiceInterface
{
public:
    virtual ~UaServiceInterface() {}

    virtual void receive(UaEncodedMessageHdr const&, OpcUaSduBuffer&) = 0;
};

using UaServiceInterfacePtr = std::unique_ptr<UaServiceInterface>;

} // namespace app::ua::service
