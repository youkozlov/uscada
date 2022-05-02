#pragma once

#include "DataType.hpp"

#include <tuple>

namespace ua
{

template <DataTypeId ID>
struct StructType
{
    StructType() = default;
    StructType(StructType const&) = delete;
    StructType& operator=(StructType const&) = delete;
    static constexpr DataTypeId Id = ID;
    std::size_t size() const { return 1; }
};

template<typename...ARGS>
bool compare(ARGS&&...args)
{
    bool result = true;
    ([&](auto&& item)
    {
        auto&& [rhs, lhs] = item;
        bool cmp = false;
        if (lhs && rhs)
        {
            cmp = *lhs == *rhs;
        }
        else
        {
            cmp = !((lhs && lhs->size()) || (rhs && rhs->size()));
        }
        result = result && cmp;
    } (args), ...);
    return result;
}

template<typename...ARGS>
std::uint8_t encodeMask(ARGS&&...args)
{
    uint8_t pos{0};
    std::uint8_t result{0};
    ([&](auto&& item)
    {
        result |= item ? (1u << pos) : 0;
        pos += 1;
    } (args), ...);
    return result;
}

template<typename...ARGS>
std::uint8_t encodeMaskSizeCheck(ARGS&&...args)
{
    uint8_t pos{0};
    std::uint8_t result{0};
    ([&](auto&& item)
    {
        result |= (item && item->size()) ? (1u << pos) : 0;
        pos += 1;
    } (args), ...);
    return result;
}

} // namespace ua
