#pragma once

#include "NodeId.hpp"
#include <optional>
#include <type_traits>

namespace app::ua
{

enum class AttributeId
{
      NodeId = 1
    , NodeClass = 2
    , BrowseName = 3
    , DisplayName = 4
    , Description = 5
    , WriteMask = 6
    , UserWriteMask = 7
    , IsAbstract = 8
    , Symmetric = 9
    , InverseName = 10
    , ContainsNoLoops = 11
    , EventNotifier = 12
    , Value = 13
    , DataType = 14
    , ValueRank = 15
    , ArrayDimensions = 16
    , AccessLevel = 17
    , UserAccessLevel = 18
    , MinimumSamplingInterval = 19
    , Historizing = 20
    , Executable = 21
    , UserExecutable = 22
    , DataTypeDefenition = 23
    , RolePermissions = 24
    , UserRolePermissions = 25
    , AccessRestrictions = 26
    , AccessLevelEx = 27
};

template <AttributeId Id, typename DataTypeIn, bool Optional = false>
class Attribute
{
using DataType = typename std::conditional<Optional, std::optional<DataTypeIn>, DataTypeIn>::type;
public:
    Attribute() = default;
    ~Attribute() = default;
    constexpr AttributeId id() const { return Id; }
    DataType const& read() const { return val; }
    void write(DataTypeIn newVal) { val = newVal; }
    bool isOptional() const { return Optional; }
private:
    DataType val;
};

template <AttributeId Id, typename DataTypeIn, bool Optional = false>
using AttributeOpt = Attribute<Id, DataTypeIn, true>;

} // namespace app::ua
