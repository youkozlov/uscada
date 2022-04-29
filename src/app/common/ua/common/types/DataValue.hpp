#pragma once

#include "StructType.hpp"
#include "Variant.hpp"

namespace ua
{

struct DataValue : public StructType<DataTypeId::DataValue>
{
    Opt<Variant> value;
    Opt<StatusCode> status;
    Opt<DateTime> sourceTimestampt;
    Opt<UInt16> sourcePicoSeconds;
    Opt<DateTime> serverTimeStampt;
    Opt<UInt16> serverPicoSeconds;

    bool operator==(DataValue const& rhs) const
    {
        return this->value == rhs.value
            && this->status == rhs.status
            && this->sourceTimestampt == rhs.sourceTimestampt
            && this->sourcePicoSeconds == rhs.sourcePicoSeconds
            && this->serverTimeStampt == rhs.serverTimeStampt
            && this->serverPicoSeconds == rhs.serverPicoSeconds;
    }
    std::uint8_t encodingMask() const
    {
        return encodeMask
        (
              value
            , status
            , sourceTimestampt
            , sourcePicoSeconds
            , serverTimeStampt
            , serverPicoSeconds
        );
    }
};

} // namespace ua
