#pragma once

#include "StructType.hpp"
#include "String.hpp"

namespace app::ua
{

struct LocalizedText : public StructType<DataTypeId::LocalizedText>
{
    Opt<String> locale;
    Opt<String> text;
    bool operator==(LocalizedText const& rhs) const
    {
        return compare
        (
              std::make_tuple(locale, rhs.locale)
            , std::make_tuple(text, rhs.text)
        );
    }
    std::uint8_t encodingMask() const
    {
        return encodeMaskSizeCheck
        (
              locale
            , text
        );
    }
};

} // namespace app::ua
