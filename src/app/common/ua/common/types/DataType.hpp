#pragma once

#include <cstdint>
#include <optional>
#include <array>
#include <vector>
#include <memory>
#include <variant>
#include "Logger.hpp"

namespace ua
{

enum class DataTypeId : std::uint8_t
{
      Undefined = 0
    , Boolean = 1
    , SByte = 2
    , Byte = 3
    , Int16 = 4
    , UInt16 = 5
    , Int32 = 6
    , UInt32 = 7
    , Int64 = 8
    , UInt64 = 9
    , Float = 10
    , Double = 11
    , String = 12
    , DateTime = 13
    , Guid = 14
    , ByteString = 15
    , XmlElement = 16
    , NodeId = 17
    , ExpandedNodeId = 18
    , StatusCode = 19
    , QualifiedName = 20
    , LocalizedText = 21
    , ExtensionObject = 22
    , DataValue = 23
    , Variant = 24
    , DiagnosticInfo = 25
};

inline std::uint8_t toUint8(DataTypeId val)
{
    return static_cast<std::uint8_t>(val);
}

template <DataTypeId ID, typename TYPE>
class NumericType
{
public:
    static constexpr DataTypeId Id = ID;
    using Type = TYPE;
    NumericType() = default;
    template <typename...ARGS>
    explicit NumericType(ARGS...args)
        : val(args...)
    {}
    NumericType& operator=(Type other)
    {
        this->val = other;
        return *this;
    }
    operator Type&() { return val; }
    operator Type() const { return val; }
private:
    TYPE val{};
};

template <DataTypeId ID>
struct StringType
{
    static constexpr DataTypeId Id = ID;

    StringType() = default;
    StringType(char const* str)
        : val(str)
    {}
    bool operator==(StringType const& rhs) const
    {
        return this->val == rhs.val;
    }
    void clear() { val.clear(); }
    std::size_t size() const { return val.size(); }
    void resize(std::size_t newSize) { val.resize(newSize); }
    char& operator[](std::size_t pos) { return val[pos]; }
    char const& operator[](std::size_t pos) const { return val[pos]; }
    std::string val{};
};

template<typename T>
using Opt = std::optional<T>;

template<typename T>
using Ptr = std::unique_ptr<T>;

template<typename T, auto SIZE>
using StaticArray = std::array<T, SIZE>;

template <typename T>
using DynamicArray = std::vector<T>;

template <typename...ARGS>
using Var = std::variant<ARGS...>;

} // namespace ua
