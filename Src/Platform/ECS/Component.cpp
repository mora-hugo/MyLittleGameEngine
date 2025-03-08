#include "ECS/Component.h"
#include "ECS/Entity.h"
HC::Component::~Component() {
    if(GetEntity() && Class()) {
        GetEntity()->RemoveComponent(Class());
    }
}
