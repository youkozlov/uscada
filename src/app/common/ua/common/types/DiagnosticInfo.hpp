#pragma once

#include "StructType.hpp"
#include "Byte.hpp"
#include "Int32.hpp"
#include "String.hpp"
#include "StatusCode.hpp"

namespace app::ua
{

struct DiagnosticInfo : public StructType<DataTypeId::DiagnosticInfo>
{
    Opt<Int32> symbolicId;
    Opt<Int32> namespaceUri;
    Opt<Int32> locale;
    Opt<Int32> localizedText;
    Opt<String> additionalInfo;
    Opt<StatusCode> innerStatusCode;
    Ptr<DiagnosticInfo> innerDiagnosticInfo;

    bool operator==(DiagnosticInfo const& rhs) const
    {
        bool cmpInnerDiagnosticInfo;
        if (this->innerDiagnosticInfo && rhs.innerDiagnosticInfo)
        {
            cmpInnerDiagnosticInfo = *this->innerDiagnosticInfo == *rhs.innerDiagnosticInfo;
        }
        else
        {
            cmpInnerDiagnosticInfo = not (this->innerDiagnosticInfo || rhs.innerDiagnosticInfo);
        }
        return this->symbolicId == rhs.symbolicId
            && this->namespaceUri == rhs.namespaceUri
            && this->locale == rhs.locale
            && this->localizedText == rhs.localizedText
            && this->additionalInfo == rhs.additionalInfo
            && this->innerStatusCode == rhs.innerStatusCode
            && cmpInnerDiagnosticInfo;
    }

    std::uint8_t encodingMask() const
    {
        return encodeMask
        (
              symbolicId
            , namespaceUri
            , locale
            , localizedText
            , additionalInfo
            , innerStatusCode
            , innerDiagnosticInfo
        );
    }
};

} // namespace app::ua
