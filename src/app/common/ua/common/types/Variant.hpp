#pragma once

#include "StructType.hpp"
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
// 0 - 21
          Boolean
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
// 22 - 
        , DynamicArray<Boolean>
        , DynamicArray<SByte>
        , DynamicArray<Byte>
        , DynamicArray<Int16>
        , DynamicArray<UInt16>
        , DynamicArray<Int32>
        , DynamicArray<UInt32>
        , DynamicArray<Int64>
        , DynamicArray<UInt64>
        , DynamicArray<Float>
        , DynamicArray<Double>
        , DynamicArray<String>
        , DynamicArray<DateTime>
        , DynamicArray<Guid>
        , DynamicArray<ByteString>
        , DynamicArray<XmlElement>
        , DynamicArray<NodeId>
        , DynamicArray<ExpandedNodeId>
        , DynamicArray<StatusCode>
        , DynamicArray<QualifiedName>
        , DynamicArray<LocalizedText>
        , DynamicArray<ExtensionObject>
    >;
    Ptr<Value> value;
    Opt<DynamicArray<Int32>> arrayDimensions;

    bool operator==(Variant const& rhs) const
    {
        bool cmpValue;
        if (this->value && rhs.value)
        {
            cmpValue = *this->value == *rhs.value;
        }
        else
        {
            cmpValue = not (this->value || rhs.value);
        }
        bool cmpArrayDimensions = *this->arrayDimensions == *rhs.arrayDimensions;
        return cmpValue && cmpArrayDimensions;
    }
    std::uint8_t encodingMask() const
    {
        // see type Value
        auto toDataTypeId = [](auto val) { return val < 22 ? val + 1 : ((val - 21) | 0x80); };
        return value ? toDataTypeId(value->index()) : 0;
    }
    template <typename T, typename...ARGS>
    T& emplace(ARGS...args)
    {
        value = std::make_unique<Variant::Value>();
        return value->emplace<T>(args...);
    }
};

} // namespace ua
