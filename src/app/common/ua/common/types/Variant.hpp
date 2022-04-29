#pragma once

#include "StructType.hpp"
#include "Undefined.hpp"
#include "Boolean.hpp"
#include "SByte.hpp"
#include "Byte.hpp"
#include "Int16.hpp"
#include "UInt16.hpp"
#include "Int32.hpp"
#include "UInt32.hpp"
#include "Int64.hpp"
#include "UInt64.hpp"
#include "Float.hpp"
#include "Double.hpp"
#include "String.hpp"
#include "DateTime.hpp"
#include "Guid.hpp"
#include "ByteString.hpp"
#include "XmlElement.hpp"
#include "NodeId.hpp"
#include "ExpandedNodeId.hpp"
#include "StatusCode.hpp"
#include "QualifiedName.hpp"
#include "LocalizedText.hpp"
#include "ExtensionObject.hpp"

namespace ua
{

struct Variant : public StructType<DataTypeId::Variant>
{
    using Value = Var
    <
          Undefined
        , Boolean
        , SByte
        , Byte
        , Int16
        , UInt16
        , Int32
        , UInt32
        , Int64
        , UInt64
        , Float
        , Double
        , String
        , DateTime
        , Guid
        , ByteString
        , XmlElement
        , NodeId
        , ExpandedNodeId
        , StatusCode
        , QualifiedName
        , LocalizedText
        , ExtensionObject
        , DynamicArray<Boolean>
        , DynamicArray<SByte>
        , DynamicArray<Byte>
        , DynamicArray<Int16>
        , DynamicArray<UInt16>
        , DynamicArray<Int32>
        , DynamicArray<UInt32>
    >;
    Opt<Int32> arrayLength;
    Value value;
    Opt<DynamicArray<Int32>> arrayDimensions;

    bool operator==(Variant const& rhs) const
    {
        bool cmpArrayLength{false};
        if (this->arrayLength && rhs.arrayLength)
        {
            cmpArrayLength = *this->arrayLength == *rhs.arrayLength;
        }
        else
        {
            cmpArrayLength = true;
        }
        bool cmpValue = this->value == rhs.value;
        bool cmpArrayDimensions{false};
        if (this->arrayDimensions && rhs.arrayDimensions)
        {
            cmpArrayDimensions = *this->arrayDimensions == *rhs.arrayDimensions;
        }
        else
        {
            cmpArrayDimensions = true;
        }
        return cmpArrayLength && cmpValue && cmpArrayDimensions;
    }
    std::uint8_t encodingMask() const
    {
        return static_cast<std::uint8_t>(value.index());
    }
};

template <typename T>
DynamicArray<T>& emplace(Variant& variant, Int32 arrayLength)
{
    auto& arr = variant.value.emplace<DynamicArray<T>>();
    arr.resize(arrayLength);
    return arr;
}

template <typename T>
T& emplace(Variant& variant)
{
    return variant.value.emplace<T>();
}


} // namespace ua
