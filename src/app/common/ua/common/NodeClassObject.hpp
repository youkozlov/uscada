#pragma once

#include "NodeClassBase.hpp"
#include "EventNotifierType.hpp"
#include "NodeClassObjectType.hpp"

namespace app::ua
{

class NodeClassObject : public NodeClassBase
{
public:
    NodeClassObject() {}
    ~NodeClassObject() {}

    Attribute<AttributeId::EventNotifier, EventNotifierType> eventNotifier;

    NodeClassBasePtr& HasComponent(std::string name) { return components[name]; }
    NodeClassObjectTypePtr& HasTypeDefinition() { return nodeClassObjectType; }

private:
    NodeClassObjectTypePtr nodeClassObjectType;
    NodeClassBaseMapPtr    components;
};

} // namespace app::ua
