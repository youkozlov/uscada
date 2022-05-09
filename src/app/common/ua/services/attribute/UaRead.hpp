#pragma once

#include "UaServiceInterface.hpp"
#include "OpcUaSecureChannel.hpp"

namespace app::ua
{

class UaAttributeController;

class UaRead : public UaServiceInterface
{
public:
    UaRead(UaAttributeController&);
    ~UaRead();

    void process(OpcUaSecureChannel&) final;

private:
    UaAttributeController& attributeController;
    std::uint32_t storedRequestHandle;
};

} // namespace app::ua
